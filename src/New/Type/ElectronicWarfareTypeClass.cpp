#include "ElectronicWarfareTypeClass.hpp"

#include <Ext/TechnoType/Body.h>
#include <Ext/BulletType/Body.h>
#include <Ext/WarheadType/Body.h>

ElectronicWarfareTypeClass::DataEntry* ElectronicWarfareTypeClass::DataEntry::Get(AbstractTypeClass* pAbsType)
{
	if (auto* pExtType = TechnoTypeExt::ExtMap.Find(abstract_cast<TechnoTypeExt::base_type*>(pAbsType)))
		return &pExtType->EW;
	if (auto* pExtType = BulletTypeExt::ExtMap.Find(abstract_cast<BulletTypeExt::base_type*>(pAbsType)))
		return &pExtType->EW;
	if (auto* pExtType = WarheadTypeExt::ExtMap.Find(abstract_cast<WarheadTypeExt::base_type*>(pAbsType)))
		return &pExtType->EW;
	return nullptr;
}

void ElectronicWarfareTypeClass::DataEntry::LoadFromINI(CCINIClass* pINI, const char* pSection)
{
	INI_EX exINI(pINI);
}

#pragma region(save/load)

template <class T>
bool ElectronicWarfareTypeClass::DataEntry::Serialize(T& stm)
{
	return stm
		.Process(this->OwnerType)
		.Success();
}

bool ElectronicWarfareTypeClass::DataEntry::Load(PhobosStreamReader& stm, bool registerForChange)
{
	return this->Serialize(stm);
}

bool ElectronicWarfareTypeClass::DataEntry::Save(PhobosStreamWriter& stm) const
{
	return const_cast<ElectronicWarfareTypeClass::DataEntry*>(this)->Serialize(stm);
}

#pragma endregion(save/load)
