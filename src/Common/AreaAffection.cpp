#include "AreaAffection.Post.hpp"

#include <FootClass.h>

#include <Ext/Cell/Body.hpp>
#include <Ext/Techno/Body.h>
#include <Ext/TechnoType/Body.h>

#include <New/Senses.hpp>
#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

void AreaAffection::CellEntry::Register(SensorClass* pSensor)
{
	if (std::find(Sensors.cbegin(), Sensors.cend(), pSensor) != Sensors.cend())
		return;
	Sensors.push_back(pSensor);
	for (auto& pCloakType : pSensor->Type->Senses)
	{
		auto& sensesMap = SensedBy[pCloakType];
		auto& senses = sensesMap[pSensor->GetOwningHouse()];
		senses.Register(pSensor);
	}
}
void AreaAffection::CellEntry::Unregister(SensorClass* pSensor)
{
	if (Sensors.remove(pSensor) == 0)
		return;
	for (auto& pCloakType : pSensor->Type->Senses)
	{
		auto& sensesMap = SensedBy[pCloakType];
		for (auto& kvp : sensesMap)
			kvp.second.Unregister(pSensor);
	}
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

std::shared_ptr<DetectResult> AreaAffection::CellEntry::DetectBy(CloakTypeClass* pCloakType, HouseClass* pSubject)
{
	auto r = std::make_shared<DetectResult>(pSubject, pCloakType);

	auto iter = std::find(SensedBy.begin(), SensedBy.end(), pCloakType);
	if (iter == SensedBy.end())
		return r;
	for (auto& pair : iter->second)
	{
		bool const isMe = pSubject == pair.first;
		bool const isAlly = pSubject->IsAlliedWith(pair.first);
		if (!isMe && !isAlly)
			continue;

		auto const& senses = pair.second;
		senses.Air.Detect(r->Air.Sensors, r->Air.Decloakers, !isMe);
		senses.Ground.Detect(r->Ground.Sensors, r->Ground.Decloakers, !isMe);
		senses.Subterannean.Detect(r->Subterannean.Sensors, r->Subterannean.Decloakers, !isMe);
	}
	return r;
}


template<typename ...TAreaAffectionDataEntries>
	requires (AreaAffection::IsDataEntry<TAreaAffectionDataEntries> && ...)
inline void __PerCellProcess(
	FootClass* pThis, TechnoExt::ExtData* pExt
	, TechnoTypeClass* pType, TechnoTypeExt::ExtData* pTypeExt
	, typename TAreaAffectionDataEntries& ...entries
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

void AreaAffection::PerCellProcess(
	FootClass* pThis, TechnoExt::ExtData* pExt
	, TechnoTypeClass* pType, TechnoTypeExt::ExtData* pTypeExt
) {
	__PerCellProcess(pThis, pExt, pType, pTypeExt
		, pExt->AreaAffection->Sensor
		, pExt->AreaAffection->Cloak
		, pExt->AreaAffection->EW
	);
}

