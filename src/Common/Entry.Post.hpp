#pragma once

#include <TechnoClass.h>
#include <TechnoTypeClass.h>
#include <BulletClass.h>
#include <BulletTypeClass.h>
#include <WarheadTypeClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/WarheadType/Body.h>

#include <Common/Entry.Pre.hpp>
#include <New/Type/SensorTypeClass.hpp>
#include <New/Type/CloakTypeClass.hpp>
#include <New/Type/ElectronicWarfareTypeClass.hpp>

inline SensorTypeClass::data_entry* SensorTypeClass::EntryOf(AbstractTypeClass* pAbsType)
{
	if (auto* pExtType = TechnoTypeExt::ExtMap.Find(type_cast<TechnoTypeExt::base_type*>(pAbsType)))
		return &pExtType->Sensor;
	if (auto* pExtType = BulletTypeExt::ExtMap.Find(type_cast<BulletTypeExt::base_type*>(pAbsType)))
		return &pExtType->Sensor;
	if (auto* pExtType = WarheadTypeExt::ExtMap.Find(type_cast<WarheadTypeExt::base_type*>(pAbsType)))
		return &pExtType->Sensor;
	return nullptr;
}

template<typename TExtension>
inline SensorTypeClass::data_entry& SensorTypeClass::EntryOf(typename TExtension::ExtData* pExt)
{
	return pExt->Sensor;
}

inline CloakTypeClass::data_entry* CloakTypeClass::EntryOf(AbstractTypeClass* pAbsType)
{
	if (auto* pExtType = TechnoTypeExt::ExtMap.Find(type_cast<TechnoTypeExt::base_type*>(pAbsType)))
		return &pExtType->Cloak;
	if (auto* pExtType = BulletTypeExt::ExtMap.Find(type_cast<BulletTypeExt::base_type*>(pAbsType)))
		return &pExtType->Cloak;
	if (auto* pExtType = WarheadTypeExt::ExtMap.Find(type_cast<WarheadTypeExt::base_type*>(pAbsType)))
		return &pExtType->Cloak;
	return nullptr;
}

template<typename TExtension>
inline CloakTypeClass::data_entry& CloakTypeClass::EntryOf(typename TExtension::ExtData* pExt)
{
	return pExt->Cloak;
}

inline ElectronicWarfareTypeClass::data_entry* ElectronicWarfareTypeClass::EntryOf(AbstractTypeClass* pAbsType)
{
	if (auto* pExtType = TechnoTypeExt::ExtMap.Find(type_cast<TechnoTypeExt::base_type*>(pAbsType)))
		return &pExtType->EW;
	if (auto* pExtType = BulletTypeExt::ExtMap.Find(type_cast<BulletTypeExt::base_type*>(pAbsType)))
		return &pExtType->EW;
	if (auto* pExtType = WarheadTypeExt::ExtMap.Find(type_cast<WarheadTypeExt::base_type*>(pAbsType)))
		return &pExtType->EW;
	return nullptr;
}

template<typename TExtension>
inline ElectronicWarfareTypeClass::data_entry& ElectronicWarfareTypeClass::EntryOf(typename TExtension::ExtData* pExt)
{
	return pExt->EW;
}
