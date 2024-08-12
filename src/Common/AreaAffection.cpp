#include "AreaAffection.Body.hpp"
#include "AreaAffection.Post.hpp"

#include <FootClass.h>

#include <Ext/Cell/Body.hpp>
#include <Ext/Techno/Body.h>
#include <Ext/TechnoType/Body.h>

#include <New/Senses.hpp>
#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

decltype(AreaAffection::IInstance::Array) AreaAffection::IInstance::Array;

void AreaAffection::CellEntry::Register(SensorClass* pSensor)
{
	if (std::find(Items.cbegin(), Items.cend(), pSensor) != Items.cend())
		return;
	Items.push_back(pSensor);
	for (auto& pCloakType : pSensor->Type->Scan)
	{
		auto& sensesMap = ScannedBy[pCloakType];
		auto& senses = sensesMap[pSensor->GetOwningHouse()];
		senses.Register(pSensor);
	}

	ScanCacheDirty = true;
}
void AreaAffection::CellEntry::Unregister(SensorClass* pSensor)
{
	if (Items.remove(pSensor) == 0)
		return;
	for (auto& pCloakType : pSensor->Type->Scan)
	{
		auto& sensesMap = ScannedBy[pCloakType];
		for (auto& kvp : sensesMap)
			kvp.second.Unregister(pSensor);
	}

	ScanCacheDirty = true;
}

void AreaAffection::CellEntry::Register(CloakClass* pCloak)
{
	if (std::find(Cloaks.cbegin(), Cloaks.cend(), pCloak) != Cloaks.cend())
		return;
	Cloaks.push_back(pCloak);
}
void AreaAffection::CellEntry::Unregister(CloakClass* pCloak)
{
	if (Cloaks.remove(pCloak) == 0)
		return;
}

void AreaAffection::CellEntry::Register(ElectronicWarfareClass* pEW)
{
	if (std::find(EWs.cbegin(), EWs.cend(), pEW) != EWs.cend())
		return;
	EWs.push_back(pEW);
}
void AreaAffection::CellEntry::Unregister(ElectronicWarfareClass* pEW)
{
	if (EWs.remove(pEW) == 0)
		return;
}

std::shared_ptr<Senses::ScanResult> AreaAffection::CellEntry::ScanBy(CloakTypeClass* pCloakType, HouseClass* pSubject)
{
	if(!ScanCacheDirty)
	{
		auto it = ScanCache.find({ pCloakType, pSubject });
		if (it != ScanCache.end())
			return it->second;
	}
	else
	{
		ScanCacheDirty = false;
		ScanCache.clear();
	}

	auto r = std::make_shared<Senses::ScanResult>(pSubject, pCloakType);

	auto iter = ScannedBy.find(pCloakType);
	if (iter == ScannedBy.end())
		return r;
	for (auto& pair : iter->second)
	{
		auto const& senses = pair.second;
		bool const isMe = pSubject == pair.first;
		bool const isAlly = pSubject->IsAlliedWith(pair.first);
		for (auto p : {
			  std::pair<decltype(senses.Air) const&, decltype(r->Air)&>(senses.Air, r->Air)
			, std::pair<decltype(senses.Air) const&, decltype(r->Air)&>(senses.Ground, r->Ground)
			, std::pair<decltype(senses.Air) const&, decltype(r->Air)&>(senses.Subterannean, r->Subterannean)
		})
			p.first.Scan(!isMe, !isMe && !isAlly
				, p.second.Items
				, p.second.Detectors, p.second.Selectables
				, p.second.Decloakers
				, p.second.Trackers
				, p.second.Displayers
			);
	}
	return r;
}


template<typename ...TDataEntries>
	requires (AreaAffection::IsDataEntry<TDataEntries> && ...)
inline void FootClass__PerCellProcess(
	FootClass* pThis, TechnoExt::ExtData* pExt
	, TechnoTypeClass* pType, TechnoTypeExt::ExtData* pTypeExt
	, typename TDataEntries& ...entries
) {
	short radius; int radiusSquared;
	AreaAffection::MaxRanges(radius, radiusSquared, entries...);

	auto lastMapCoords = pThis->LastMapCoords;
	auto currentMapCoords = pThis->CurrentMapCoords;

	auto cellHandler = [&](int radiusSq,
		CellClass* pCurrent, CellExt::ExtData* pCurrentExt, 
		CellClass* pPrevious, CellExt::ExtData* pPreviousExt)
	{
		/* default sensors logic */
		if (pType->SensorsSight > 0)
		{
			// See 0x4DE780 and 0x4DE940
			pPrevious->Sensors_RemOfHouse(pThis->GetOwningHouseIndex());
			pCurrent->Sensors_AddOfHouse(pThis->GetOwningHouseIndex());
		}

		AreaAffection::InOut(radius, radiusSq, pCurrentExt, pPreviousExt, entries...);
	};
}

template<typename ...TDataEntries>
	requires (AreaAffection::IsDataEntry<TDataEntries> && ...)
inline void BulletClass__PerCellProcess(
	BulletClass* pThis, BulletExt::ExtData* pExt
	, BulletTypeClass* pType, BulletTypeExt::ExtData* pTypeExt
	, typename TDataEntries& ...entries
) {
	short radius; int radiusSquared;
	AreaAffection::MaxRanges(radius, radiusSquared, entries...);

	auto lastMapCoords = pThis->LastMapCoords;
	auto currentMapCoords = pThis->GetMapCoords();

	auto cellHandler = [&](int radiusSq,
		CellClass* pCurrent, CellExt::ExtData* pCurrentExt,
		CellClass* pPrevious, CellExt::ExtData* pPreviousExt)
	{
		// TODO: make default sensors and cloak as separate classes for area affection.
		/* default sensors logic */
		/*
		if (pType->SensorsSight > 0)
		{
			// See 0x4DE780 and 0x4DE940
			pPrevious->Sensors_RemOfHouse(pThis->GetOwningHouseIndex());
			pCurrent->Sensors_AddOfHouse(pThis->GetOwningHouseIndex());
		}
		*/

		AreaAffection::InOut(radius, radiusSq, pCurrentExt, pPreviousExt, entries...);
	};
}

void AreaAffection::PerCellProcess(
	FootClass* pThis, TechnoExt::ExtData* pExt
	, TechnoTypeClass* pType, TechnoTypeExt::ExtData* pTypeExt
) {
	FootClass__PerCellProcess(pThis, pExt, pType, pTypeExt
		, pExt->AreaAffection->Sensor
		, pExt->AreaAffection->Cloak
		, pExt->AreaAffection->EW
	);
}

void AreaAffection::PerCellProcess(
	BulletClass* pThis, BulletExt::ExtData* pExt
	, BulletTypeClass* pType, BulletTypeExt::ExtData* pTypeExt
) {
	BulletClass__PerCellProcess(pThis, pExt, pType, pTypeExt
		, pExt->AreaAffection->Sensor
		, pExt->AreaAffection->Cloak
		, pExt->AreaAffection->EW
	);
}

void AreaAffection::InitializeOnCell(IInstance* pInst, CellClass* cell)
{
	CellExt::ForEachCell(cell->MapCoords, pInst->Radius.Get(), pInst->RadiusSq.Get(), [&pInst](
		  int radius
		, int radiusSq
		, CellClass* pCell
		, CellExt::ExtData* pExt
	) {
		pInst->In(*pExt, radius, radiusSq);
	});
}
