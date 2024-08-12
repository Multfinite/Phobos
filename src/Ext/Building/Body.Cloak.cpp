#include "Body.h"

#include <HouseClass.h>
#include <BuildingClass.h>

#include <Ext/Cell/Body.hpp>
#include <Common/AreaAffection.Post.hpp>

#include <ParticleSystemClass.h>

void BuildingExt::ExtData::CloakingAI(bool __unused)
{
	auto& b = *OwnerObject();
	auto* bTypeExt = TypeExtData;
	auto* bType = TypeExtData->OwnerObject();
	auto* tType = b.GetTechnoType();
	auto* tTypeExt = TechnoTypeExt::ExtMap.Find(tType);

	// if (!bType) return; // idk why it here. I think it is impossible --Multfinite

	switch (b.CloakState)
	{
		case(CloakState::Cloaking):
		{
			if (b.Translucency >= 15) break;

			++b.Translucency;
			b.NeedsRedraw = b.NeedsRedraw
				|| b.Translucency == 1
				|| b.Translucency == 6
				|| b.Translucency == 11;
			char translucency = b.Translucency + (b.Translucency == 15 && b.VisualCharacter(false, nullptr) == VisualType::Hidden) ? 1 : 0;
			for (auto* anim : b.Anims)
				anim->TranslucencyLevel = translucency;

			if (b.Translucency == 15)
			{
				b.CloakState = CloakState::Cloaked;
				GameDelete(b.NaturalParticleSystem);
				b.NaturalParticleSystem = nullptr;
			}
		} break;
		case(CloakState::Uncloaking):
		{
			if (b.Translucency < 0) break;

			b.Translucency = b.Translucency > 0 ? b.Translucency - 1 : 0;
			b.NeedsRedraw = b.NeedsRedraw
				|| b.Translucency > 0
				|| b.Translucency == 5
				|| b.Translucency == 10;
			char translucency = b.Translucency + (b.Translucency == 15 && b.VisualCharacter(false, nullptr) == VisualType::Hidden) ? 1 : 0;
			for (auto* anim : b.Anims)
				anim->TranslucencyLevel = translucency;

			if (b.Translucency) break;

			b.CloakState = CloakState::Uncloaked;

			if (b.NaturalParticleSystem) break;
			if (*Unsorted::BuildingDefaultCoords == bType->NaturalParticleSystemLocation) break;

			b.NaturalParticleSystem = new ParticleSystemClass(
				bType->NaturalParticleSystem
				, b.Location + bType->NaturalParticleSystemLocation
				, b.GetCell() /*MapClass::Instance->GetTargetCell(b.Location)*/
				, nullptr
				, *Unsorted::BuildingDefaultCoords
				, nullptr
			);
		} break;
		case(CloakState::Cloaked):
		{
			if (!b.ShouldNotBeCloaked()) break;
			b.Uncloak(false);
		} break;
		case(CloakState::Uncloaked):
		{
			if (!b.IsReadyToCloak()) break;
			b.Cloak(false);
		} break;
	}

	// Here must be some cloak generator code.
	// But vanilla cloak generator is not fully implemented.
	// I didn't reimplement this part because i have my own implementation of cloakgen.
	// --Multfinite
	/*
	if (!(b.HasCloakingData && bType->CloakGenerator)) return;
	*/
}
