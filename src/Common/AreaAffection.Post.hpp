#pragma once

#include <TechnoClass.h>
#include <TechnoTypeClass.h>
#include <BulletClass.h>
#include <BulletTypeClass.h>
#include <WarheadTypeClass.h>

#include <Ext/Cell/Body.hpp>
#include <Ext/Traits.Cell.hpp>

#include <Ext/Techno/Body.h>
#include <Ext/TechnoType/Body.h>
#include <Ext/Traits.Techno.hpp>

#include <Ext/Bullet/Body.h>
#include <Ext/BulletType/Body.h>
#include <Ext/Traits.Bullet.hpp>

#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>
#include <New/Senses.hpp>

#include <Common/AreaAffection.hpp>

#include "Entry.Impl.hpp"

namespace AreaAffection
{
	/*!
	* @brief All affections (for FootClass) must be invoked here. Just register it inside.
	*/
	void PerCellProcess(
		FootClass* pThis, TechnoExt::ExtData* pExt
		, TechnoTypeClass* pType, TechnoTypeExt::ExtData* pTypeExt
	);

	/*!
	* @brief All affections (for BulletClass) must be invoked here. Just register it inside.
	*/
	void PerCellProcess(
		BulletClass* pThis, BulletExt::ExtData* pExt
		, BulletTypeClass* pType, BulletTypeExt::ExtData* pTypeExt
	);

	/*!
	* @author Multfinite
	* @brief Per-extension data block with inforamtion of all area affections.
	* @brief It's here to be easy in control.
	* @brief Always must be included to extension data as field `AreaAffection::InstanceEntry* const AreaAffection`
	*/
	struct InstanceEntry
	{
		data_entry<SensorClass> Sensor;
		data_entry<CloakClass> Cloak;
		data_entry<ElectronicWarfareClass> EW;

		InstanceEntry(class AbstractClass* ownerObject) :
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
		
		inline bool Load(PhobosStreamReader& Stm, bool RegisterForChange)
		{
			return Serialize(Stm);
		}
		inline bool Save(PhobosStreamWriter& Stm) const 
		{
			using this_ptr = std::remove_const_t<std::remove_pointer_t<decltype(this)>>*;
			return const_cast<this_ptr>(this)->Serialize(Stm);
		}
	private:
		template<typename T>
		inline bool Serialize(T& Stm)
		{
			return Stm
				.Process(this->Sensor)
				.Process(this->Cloak)
				.Process(this->EW)
				.Success();
		}
	};

	/*!
	* @author Multfinite
	* @brief Cell extension data block with cache of all area affection types.
	* @brief Included to cell extension as `AreaAffection::InstanceEntry* const AreaAffectionCache`
	* @brief NOTE: you must specify new `Register/Unregister` function pair for each new instance type of area affection as overload.
	*/
	struct CellEntry
	{
		// Current presented objects which works centered on this cell

		std::list<SensorClass*> Items;
		std::list<CloakClass*> Cloaks;
		std::list<ElectronicWarfareClass*> EWs;

		// [Scan for CloakTypeClass][Scan by House]
		ValueableMap<CloakTypeClass*, ValueableMap<HouseClass*, Senses::Scan>> ScannedBy;

		// [Illusion by CloakType][Illusion for House]
		ValueableMap<CloakType*, ValueableMap<HouseClass*, Senses::Illusion>> IllusionBy;

		void Register(SensorClass* pSensor);
		void Register(CloakClass* pCloak);
		void Register(ElectronicWarfareClass* pEW);

		void Unregister(SensorClass* pSensor);
		void Unregister(CloakClass* pCloak);
		void Unregister(ElectronicWarfareClass* pEW);

		struct DetectResultKey
		{
			CloakTypeClass* CloakType;
			HouseClass* Subject;

			constexpr bool operator==(DetectResultKey const& o) const noexcept { return CloakType == o.CloakType && Subject == o.Subject; }
			constexpr bool operator!=(DetectResultKey const& o) const noexcept { return !(*this == o); }
		};

		struct DetectResultKeyHasher
		{
			std::size_t operator()(const AreaAffection::CellEntry::DetectResultKey& t) const
			{
				std::size_t ret = 0; hash_combine(ret, reinterpret_cast<std::uintptr_t>(t.CloakType), reinterpret_cast<std::uintptr_t>(t.Subject)); return ret;
			}
		};

		bool ScanCacheDirty = false;
		ValueableMap<DetectResultKey, std::shared_ptr<Senses::ScanResult>, DetectResultKeyHasher> ScanCache;

		std::shared_ptr<Senses::ScanResult> ScanBy(
			CloakTypeClass* pCloakType,
			HouseClass* pSubject
		);

		bool IllusoryCacheDirty = false;
		ValueableMap<HouseClass*, Senses::IllusionResult> IllusoryCache;

		std::shared_ptr<Senses::IllusionResult> IllusoryOf(
			HouseClass* pSubject
		);
	};
}
	/* Place all your specialization for generalized logic here. --Multfinite */

template<> struct entry<SensorClass>
{
	using type = data_entry<SensorClass>;

	template<typename TExtension>
	inline static constexpr type& of(typename TExtension::ExtData& ext) noexcept { return ext.AreaAffection->Sensor; }

	inline static type* of(AbstractClass& abs) noexcept
	{
		if (auto* pExt = TechnoExt::ExtMap.Find(abstract_cast<TechnoClass*>(&abs)))
			return &pExt->AreaAffection->Sensor;
		if (auto* pExt = BulletExt::ExtMap.Find(abstract_cast<BulletClass*>(&abs)))
			return &pExt->AreaAffection->Sensor;
		if (auto* pExt = CellExt::ExtMap.Find(abstract_cast<CellClass*>(&abs)))
			return &pExt->AreaAffection->Sensor;
		return nullptr;
	}
};

template<> struct entry<CloakClass>
{
	using type = data_entry<CloakClass>;

	template<typename TExtension>
	inline static constexpr type& of(typename TExtension::ExtData& ext) noexcept { return ext.AreaAffection->Cloak; }

	inline static type* of(AbstractClass& abs) noexcept
	{
		if (auto* pExt = TechnoExt::ExtMap.Find(abstract_cast<TechnoClass*>(&abs)))
			return &pExt->AreaAffection->Cloak;
		if (auto* pExt = BulletExt::ExtMap.Find(abstract_cast<BulletClass*>(&abs)))
			return &pExt->AreaAffection->Cloak;
		if (auto* pExt = CellExt::ExtMap.Find(abstract_cast<CellClass*>(&abs)))
			return &pExt->AreaAffection->Cloak;
		return nullptr;
	}
};

template<> struct entry<ElectronicWarfareClass>
{
	using type = data_entry<ElectronicWarfareClass>;

	template<typename TExtension>
	inline static constexpr type& of(typename TExtension::ExtData& ext) noexcept { return ext.AreaAffection->EW; }

	inline static type* of(AbstractClass& abs) noexcept
	{
		if (auto* pExt = TechnoExt::ExtMap.Find(abstract_cast<TechnoClass*>(&abs)))
			return &pExt->AreaAffection->EW;
		if (auto* pExt = BulletExt::ExtMap.Find(abstract_cast<BulletClass*>(&abs)))
			return &pExt->AreaAffection->EW;
		if (auto* pExt = CellExt::ExtMap.Find(abstract_cast<CellClass*>(&abs)))
			return &pExt->AreaAffection->EW;
		return nullptr;
	}
};

namespace AreaAffection
{
	template<typename TAreaAffection, typename TExtension>
	inline void Initialize(typename TExtension::base_type* pParent)
	{
		using extension_type = typename extension_traits<TExtension>::type;

		auto* pExt = TExtension::ExtMap.Find(pParent);
		auto* pType = pParent->GetTechnoType();
		auto* pTypeExt = pExt->TypeExtData;
		data_entry<TAreaAffection>& pExtEntry = entry<TAreaAffection>::of<TExtension>(*pExt);
		auto& pExtTypeEntry = entry<typename TAreaAffection::type>::of<extension_type>(*pTypeExt);

		if (!pExtTypeEntry.IsEnabled) return;
		auto typeIter = pExtTypeEntry.Types.begin();
		auto radiusIter = pExtTypeEntry.Radiuses.begin();
		while (typeIter != pExtTypeEntry.Types.end())
		{
			TAreaAffection* pInst = Instantiate(pExtEntry, *typeIter, (HouseClass*) nullptr, (short) *radiusIter);
			++typeIter; ++radiusIter;
		}
	};

	template<typename TAreaAffection, typename TExtension, typename TPrefixLamba, typename TBodyLambda>
	inline void Initialize(typename TExtension::base_type* pParent
		, TPrefixLamba&& pl, TBodyLambda&& bl
	) {
		using extension_type = typename extension_traits<TExtension>::type;

		auto* pExt = TExtension::ExtMap.Find(pParent);
		auto* pType = pParent->GetTechnoType();
		auto* pTypeExt = pExt->TypeExtData;
		auto& pExtEntry = entry<TAreaAffection>::of<TExtension>(*pExt);
		auto& pExtTypeEntry = entry<typename TAreaAffection::type>::of<extension_type>(*pTypeExt);

		if (!pExtTypeEntry.IsEnabled) return;
		auto typeIter = pExtTypeEntry.Types.begin();
		auto radiusIter = pExtTypeEntry.Radiuses.begin();
		pl(pParent, pExt, pType, pTypeExt, pExtEntry, pExtTypeEntry);
		while (typeIter != pExtTypeEntry.Types.end())
		{			
			TAreaAffection* pInst = Instantiate(pExtEntry, *typeIter, (HouseClass*) nullptr, (short) *radiusIter);
			bl(pParent, pExt, pType, pTypeExt, pExtEntry, pExtTypeEntry
				, pInst, *typeIter, *radiusIter
			);
			++typeIter; ++radiusIter;
		}
	};
}

template<typename TExtension>
inline void SensorTypeClass::Initialize(typename TExtension::base_type* pParent) { AreaAffection::Initialize<SensorClass, TExtension>(pParent); }

template<typename TExtension>
inline void CloakTypeClass::Initialize(typename TExtension::base_type* pParent)
{
	using TAreaAffection = CloakClass;
	using extension_type = typename extension_traits<TExtension>::type;

	auto* pExt = TExtension::ExtMap.Find(pParent);
	auto* pType = pParent->GetTechnoType();
	auto* pTypeExt = pExt->TypeExtData;
	auto& pExtEntry = entry<TAreaAffection>::of<TExtension>(*pExt);
	auto& pExtTypeEntry = entry<typename TAreaAffection::type>::of<extension_type>(*pTypeExt);

	if (!pExtTypeEntry.IsEnabled) return;
	auto typeIter = pExtTypeEntry.Types.begin();
	auto radiusIter = pExtTypeEntry.Radiuses.begin();
	auto selfIter = pExtTypeEntry.Self.begin();
	while (typeIter != pExtTypeEntry.Types.end())
	{
		TAreaAffection* pInst = Instantiate(pExtEntry, *typeIter, (HouseClass*) nullptr, (short)*radiusIter);
		pInst->Self = *selfIter;
		++typeIter; ++radiusIter; ++selfIter;
	}
}

template<typename TExtension>
inline void ElectronicWarfareTypeClass::Initialize(typename TExtension::base_type* pParent) { AreaAffection::Initialize<ElectronicWarfareClass, TExtension>(pParent); }
