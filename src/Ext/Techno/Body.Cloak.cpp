#include "Body.h"

#include <HouseClass.h>
#include <BuildingClass.h>

#include <Ext/Cell/Body.hpp>
#include <Common/AreaAffection.Post.hpp>

bool TechnoExt::IsCloakedExternally(TechnoClass* pThis, CellClass* cell)
{
	return IsCloakedExternally(pThis, TechnoExt::ExtMap.Find(pThis), cell, CellExt::ExtMap.Find(cell));
}
bool TechnoExt::IsCloakedExternally(
	  TechnoClass* pThis
	, TechnoExt::ExtData* pExt
	, CellClass* cell
	, __CellExt_ExtData* cellExt
) {
	auto& deCloak = AreaAffection::Entry<CloakClass, std::remove_pointer_t<decltype(pExt)>>::Of(pExt);

	auto original = [&]() -> bool
	{
		return cell->CloakGen_InclHouse(HouseClass::CurrentPlayer->ArrayIndex);
	};

	bool isCloaked = false;
	for (auto& instance : deCloak.Items)
	{
		auto r = cellExt->AreaAffectionCache->IllusoryOf(HouseClass::CurrentPlayer);
		try
		{
			auto& g = r->GroupOf(pThis);
			isCloaked = isCloaked || g.IsStealthed();
		}
		catch (const std::exception& ex)
		{
			return original();
		}
	}

	return isCloaked || original();
}

bool TechnoExt::ExtData::IsCloakedExternally()
{
	return TechnoExt::IsCloakedExternally(
		OwnerObject(), this
		, OwnerObject()->GetCell()
		, CellExt::ExtMap.Find(OwnerObject()->GetCell())
	);
}

bool TechnoExt::ExtData::IsCloakable()
{
	auto pThis = OwnerObject();
	auto& instances = AreaAffection->Cloak.ByCloakType[CloakType::Stealth];

	return (pThis->Cloakable
		|| std::find_if(instances.cbegin(), instances.cend(), [](CloakClass const* x)
		{
			return x->Self;
		}) != instances.cend()
	);
}

bool TechnoExt::ExtData::IsReadyToCloak()
{
	auto pThis = OwnerObject();
	auto cell = pThis->GetCell();
	auto cellExt = CellExt::ExtMap.Find(cell);
	auto pTypeExt = this->TypeExtData;
	auto pType = pTypeExt->OwnerObject();

	auto endCheck = [&]() -> bool
	{
		return (
			pThis->LocomotorSource
			|| (pThis->AbstractFlags & AbstractFlags::Foot) != AbstractFlags::Foot
			/* TODO: add flag to control cloaking under iron curtain. */
			|| !pThis->IronCurtainTimer.HasStarted()
		) && pThis->GetHeight() <= 0;
	};

	/* If the object cannot recloak, then it certainly is not allowed to start. */

	if (!(IsCloakable()
		|| (pThis->Veterancy.IsVeteran() && pType->VeteranAbilities.CLOAK)
		|| (pThis->Veterancy.IsElite() && pType->EliteAbilities.CLOAK)
		|| IsCloakedExternally()
	)) {
		return false;
	}

	/* If it is already cloaked or in the process of cloaking, then it can't start cloaking. */

	if (pThis->CloakState == CloakState::Cloaked)
		return false;

	/* If the object is currently rearming, then don't begin to recloak. */

	if (!pThis->DiskLaserTimer.Completed())
		return false;

	/* If it seems like this object is about to fire on a target, then don't begin cloaking either. */

	// TODO: rewrite this to check if weapon allow to fire from cloak.
	// TODO: Add flag for weapon.

	if (pThis->Target && pThis->IsCloseEnoughToAttack(pThis->Target))
		return false;

	/* ??? */

	if (!abstract_cast<BuildingClass*>(pThis) && pThis->CloakProgress.Value)
		return false;

	/* If the arbitrary cloak delay value is still counting down, then don't allow recloaking just yet. */

	if (!pThis->CloakDelayTimer.Completed())
		return false;

	return endCheck();
}

void TechnoExt::ExtData::RetargetingCloak()
{
	auto* pThis = OwnerObject();
	
	auto coords = pThis->GetCenterCoords();
	auto cellCoords = CellClass::Coord2Cell(coords);
	auto* cell = MapClass::Instance->GetCellAt(cellCoords);
	
	bool selectable = false;
	if (pThis->CloakState == CloakState::Cloaked
		&& pThis->GetOwningHouse() != HouseClass::CurrentPlayer
		&& !(IsDetectedBy(HouseClass::CurrentPlayer, &selectable) && selectable))
		pThis->Deselect();
	
	if (IsReadyToCloak())
	{
		std::list<TechnoClass*> items;
		for (TechnoClass* techno : *TechnoClass::Array)
		{
			if (techno->LocomotorTarget != pThis) continue;
	
			auto technoCell = MapClass::Instance->GetCellAt(CellClass::Coord2Cell(techno->GetCenterCoords()));
			if (IsDetectedBy(HouseClass::CurrentPlayer, &selectable) || techno->GetOwningHouse() == pThis->GetOwningHouse())
				items.push_back(techno);
		}
		pThis->Cloak(false); // TODO: should we make an option here? it is original value
		for (TechnoClass* techno : items)
			techno->SetTarget(pThis);
	}
}

void TechnoExt::ExtData::CloakingAI(bool a2)
{
	TechnoClass& t = *OwnerObject();

	/*
	* If this object is uncloaked, but it can be cloaked and it thinks that it
	* is a good time do so, then begin cloaking. 
	*/

	if (t.CloakState != CloakState::Uncloaked)
	{
		t.CloakProgress.Update();
		t.CloakProgress.Value = t.CloakProgress.Value < 0 ? 0 : t.CloakProgress.Value;
		switch (t.CloakState)
		{
			/*
			* Handle the cloaking process. Always mark to redraw the object
			* and when the cloaking process is complete, stabilize into the
			* normal cloaked state.
			*/
			case(CloakState::Cloaking):
			{
				t.Mark(MarkType::Change);
				if (!t.CloakProgress.Rate)
					t.CloakProgress.Start(1);
				auto visualType = t.VisualCharacter(true, nullptr);

				if (visualType != VisualType::Darken)
				{
					if (visualType == VisualType::Hidden && visualType != VisualType::Shadowy) break;

					t.CloakState = CloakState::Cloaked;
					t.CloakProgress.Rate = 0;
					t.CloakProgress.Value = 0;
					t.CloakProgress.Timer.Stop();
					/*
					t.CloakProgress.Timer.StartTime = Unsorted::CurrentFrame;
					t.CloakProgress.Timer.CurrentTime = *Unsorted::CurrentFrame;
					t.CloakProgress.Timer.TimeLeft = 0;
					*/

					t.Mark(MarkType::Change); // wtf why second call?

					UnitClass* unit = abstract_cast<UnitClass*>(&t);

					/*
					* Special check to ensure that if the unit is carrying a captured
					* flag, it will never fully cloak.
					*/
					if (!unit || unit->FlagHouseIndex == -1)
					{
						t.Disappear(false);
						for (TechnoClass* techno : *TechnoClass::Array)
						{
							if (techno->Target != &t) continue;
							if (IsDetectedBy(techno->GetOwningHouse()))
								techno->SetTarget(&t);
						}
					}
					else t.Reveal();
					/*
					* A computer controlled unit will try to scatter if possible so
					* that it will be much harder to locate.
					*/
					if (unit && !t.GetOwningHouse()->IsControlledByCurrentPlayer())
						t.Scatter(Unsorted::TechnoDefaultCoords, true, false);
				}
				else if (
					t.GetHealthPercentage() <= RulesClass::Instance->ConditionRed
					&& ScenarioClass::Instance->Random.RandomRanged(0, 99) < 10
				)
					t.Uncloak(true);				
			} break;
			case(CloakState::Cloaked):
			{
				/*
				* A cloaked object will always be redrawn if it is owned by the
				* player. This ensures that the shimmering effect will animate.
				*/
				if (t.ShouldNotBeCloaked())
					t.Uncloak(false);
			} break;
			case(CloakState::Uncloaking):
			{
				t.Mark(MarkType::Change);
				auto visualType = t.VisualCharacter(true, false);

				switch (visualType)
				{
					case(VisualType::Normal): break;
					case(VisualType::Indistinct):
					{
						if (!IsReadyToCloak()) break;
						t.Cloak(true);
					} break;					
					default:
					{
						t.CloakState = CloakState::Uncloaking;

						t.CloakProgress.Rate = 0;
						t.CloakProgress.Value = 0;
						t.CloakProgress.Timer.Stop();
						t.CloakDelayTimer.Start(900 /* TICKS_PER_MINUTE_F */ * RulesClass::Instance->CloakDelay);

						t.Mark(MarkType::Change);
					} break;
				}
			} break;
		}
	}
	else
	{
		if (!(
			IsCloakable()
			&& !t.IsUnderEMP()
			&& !t.IsParalyzed()
			&& !t.IsBeingWarpedOut()
			&& !t.IsWarpingIn()
			|| (t.Veterancy.IsVeteran() && t.GetTechnoType()->VeteranAbilities.CLOAK)
			|| (t.Veterancy.IsElite() && t.GetTechnoType()->EliteAbilities.CLOAK)
		)) return;

		auto link = t.GetNthLink();
		if (!link
			|| !abstract_cast<BuildingClass*>(link)
			|| !((BuildingTypeClass*) link->GetTechnoType())->WeaponsFactory
		) {
			t.CloakProgress.Update();
		}
	}
}
