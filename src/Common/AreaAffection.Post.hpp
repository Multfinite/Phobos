#pragma once

#include <Ext/Cell/Body.hpp>
#include <Ext/Techno/Body.h>
#include <Ext/TechnoType/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/BulletType/Body.h>

#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>
#include <New/Senses.hpp>

#include <Common/AreaAffection.Body.hpp>

namespace AreaAffection
{
	/*!
	* @brief All affections (for FootClass) must be invoked here. Just register it inside.
	*/
	void PerCellProcess(
		FootClass* pThis, TechnoExt::ExtData* pExt
		, TechnoTypeClass* pType, TechnoTypeExt::ExtData* pTypeExt
	);

	struct InstanceEntry
	{
		SensorClass::data_entry Sensor;
		CloakClass::data_entry Cloak;
		ElectronicWarfareClass::data_entry EW;

		InstanceEntry(AbstractClass* ownerObject) :
			Sensor(ownerObject), Cloak(ownerObject), EW(ownerObject)
		{ }

		inline void MaxRanges(short& radius, int& radiusSquared) const
		{
			AreaAffection::MaxRanges(radius, radiusSquared
				, Sensor
				, Cloak
				, EW
			);
		}
	};

	struct CellEntry
	{
		// Current presented objects which works centered on this cell

		std::list<SensorClass*> Sensors;
		std::list<CloakClass*> Cloaks;
		std::list<ElectronicWarfareClass*> EWs;

		// [Senses of CloakType][Senses of House]
		std::map<CloakTypeClass*, std::map<HouseClass*, Senses>> SensedBy;

		void Register(SensorClass* pSensor);
		void Register(CloakClass* pCloak);
		void Register(ElectronicWarfareClass* pEW);

		void Unregister(SensorClass* pSensor);
		void Unregister(CloakClass* pCloak);
		void Unregister(ElectronicWarfareClass* pEW);

		std::shared_ptr<DetectResult> DetectBy(
			CloakTypeClass* pCloakType,
			HouseClass* pSubject
		);
	};

	template<typename TExtension>
	struct Entry<SensorClass, TExtension>
	{
		inline static DataEntry<SensorClass>& Of(typename TExtension::ExtData* pExt)
		{
			return pExt->AreaAffection->Sensor;
		}
	};
	template<> inline DataEntry<SensorClass>* EntryOf(AbstractClass* pAbs)
	{
		if (auto* pExt = TechnoExt::ExtMap.Find(abstract_cast<TechnoClass*>(pAbs)))
			return &pExt->AreaAffection->Sensor;
		if (auto* pExt = BulletExt::ExtMap.Find(abstract_cast<BulletClass*>(pAbs)))
			return &pExt->AreaAffection->Sensor;
		if (auto* pExt = CellExt::ExtMap.Find(abstract_cast<CellClass*>(pAbs)))
			return &pExt->AreaAffection->Sensor;
		return nullptr;
	}

	template<typename TExtension>
	struct Entry<CloakClass, TExtension>
	{
		inline static DataEntry<CloakClass>& Of(typename TExtension::ExtData* pExt)
		{
			return pExt->AreaAffection->Cloak;
		}
	};
	template<> inline DataEntry<CloakClass>* EntryOf(AbstractClass* pAbs)
	{
		if (auto* pExt = TechnoExt::ExtMap.Find(abstract_cast<TechnoClass*>(pAbs)))
			return &pExt->AreaAffection->Cloak;
		if (auto* pExt = BulletExt::ExtMap.Find(abstract_cast<BulletClass*>(pAbs)))
			return &pExt->AreaAffection->Cloak;
		if (auto* pExt = CellExt::ExtMap.Find(abstract_cast<CellClass*>(pAbs)))
			return &pExt->AreaAffection->Cloak;
		return nullptr;
	}

	template<typename TExtension>
	struct Entry<ElectronicWarfareClass, TExtension>
	{
		inline static DataEntry<ElectronicWarfareClass>& Of(typename TExtension::ExtData* pExt)
		{
			return pExt->AreaAffection->EW;
		}
	};
	template<> inline DataEntry<ElectronicWarfareClass>* EntryOf(AbstractClass* pAbs)
	{
		if (auto* pExt = TechnoExt::ExtMap.Find(abstract_cast<TechnoClass*>(pAbs)))
			return &pExt->AreaAffection->EW;
		if (auto* pExt = BulletExt::ExtMap.Find(abstract_cast<BulletClass*>(pAbs)))
			return &pExt->AreaAffection->EW;
		if (auto* pExt = CellExt::ExtMap.Find(abstract_cast<CellClass*>(pAbs)))
			return &pExt->AreaAffection->EW;
		return nullptr;
	}

	template<typename TAreaAffection, typename TExtension>
	inline void Initialize(typename TExtension::base_type* pParent)
	{
		auto* pExt = TExtension::ExtMap.Find(pParent);
		auto* pType = pParent->GetTechnoType();
		auto* pTypeExt = pExt->TypeExtData;
		auto& pExtEntry = AreaAffection::Entry<TAreaAffection, TExtension>::Of(pExt);
		auto& pExtTypeEntry = (typename TAreaAffection::type)::EntryOf<TExtension>(pExt);

		if (!pExtTypeEntry.IsEnabled) return;
		auto typeIter = pExtTypeEntry.Types.begin();
		auto radiusIter = pExtTypeEntry.Radiuses.begin();
		while (typeIter != pExtTypeEntry.Types.end())
		{
			TAreaAffection* pInst = pExtEntry.Instantiate(*typeIter, nullptr, *radiusIter);
			++typeIter; ++radiusIter;
		}
	};
}

template<typename TExtension>
inline void SensorTypeClass::Initialize(typename TExtension::base_type* pParent) { AreaAffection::Initialize<SensorClass>(pParent); }

template<typename TExtension>
inline void CloakTypeClass::Initialize(typename TExtension::base_type* pParent) { AreaAffection::Initialize<SensorClass>(pParent); }

template<typename TExtension>
inline void ElectronicWarfareTypeClass::Initialize(typename TExtension::base_type* pParent) { AreaAffection::Initialize<SensorClass>(pParent); }
