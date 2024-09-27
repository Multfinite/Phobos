#pragma once
#include <Common/Entry.hpp>

#include <TechnoClass.h>
#include <TechnoTypeClass.h>
#include <BulletClass.h>
#include <BulletTypeClass.h>
#include <WarheadTypeClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/WarheadType/Body.h>

#include <New/Type/CloakTypeClass.hpp>
#include <New/Type/SensorTypeClass.hpp>
#include <New/Type/ElectronicWarfareTypeClass.hpp>

#include <New/Entity/CloakClass.hpp>
#include <New/Entity/SensorClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

template<> struct entry<SensorTypeClass>
{
	using type = data_entry<SensorTypeClass>;

	template<typename TExtension>
	inline static constexpr type& of(typename TExtension::ExtData& ext) noexcept { return ext.Sensor; }

	inline static type* of(AbstractTypeClass& absType) noexcept
	{
		if (auto* pExtType = TechnoTypeExt::ExtMap.Find(type_cast<TechnoTypeExt::base_type*>(&absType)))
			return &pExtType->Sensor;
		if (auto* pExtType = BulletTypeExt::ExtMap.Find(type_cast<BulletTypeExt::base_type*>(&absType)))
			return &pExtType->Sensor;
		if (auto* pExtType = WarheadTypeExt::ExtMap.Find(type_cast<WarheadTypeExt::base_type*>(&absType)))
			return &pExtType->Sensor;
		return nullptr;
	}
};

template<> struct entry<CloakTypeClass>
{
	using type = data_entry<CloakTypeClass>;

	template<typename TExtension>
	inline static constexpr type& of(typename TExtension::ExtData& ext) noexcept { return ext.Cloak; }

	inline static type* of(AbstractTypeClass& absType) noexcept
	{
		if (auto* pExtType = TechnoTypeExt::ExtMap.Find(type_cast<TechnoTypeExt::base_type*>(&absType)))
			return &pExtType->Cloak;
		if (auto* pExtType = BulletTypeExt::ExtMap.Find(type_cast<BulletTypeExt::base_type*>(&absType)))
			return &pExtType->Cloak;
		if (auto* pExtType = WarheadTypeExt::ExtMap.Find(type_cast<WarheadTypeExt::base_type*>(&absType)))
			return &pExtType->Cloak;
		return nullptr;
	}
};

template<> struct entry<ElectronicWarfareTypeClass>
{
	using type = data_entry<ElectronicWarfareTypeClass>;

	template<typename TExtension>
	inline static constexpr type& of(typename TExtension::ExtData& ext) noexcept { return ext.EW; }

	inline static type* of(AbstractTypeClass& absType) noexcept
	{
		if (auto* pExtType = TechnoTypeExt::ExtMap.Find(type_cast<TechnoTypeExt::base_type*>(&absType)))
			return &pExtType->EW;
		if (auto* pExtType = BulletTypeExt::ExtMap.Find(type_cast<BulletTypeExt::base_type*>(&absType)))
			return &pExtType->EW;
		if (auto* pExtType = WarheadTypeExt::ExtMap.Find(type_cast<WarheadTypeExt::base_type*>(&absType)))
			return &pExtType->EW;
		return nullptr;
	}
};
