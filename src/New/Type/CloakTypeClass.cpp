#include "CloakTypeClass.hpp"

#include <Ext/TechnoType/Body.h>
#include <Ext/BulletType/Body.h>
#include <Ext/WarheadType/Body.h>

CloakTypeClass::DataEntry* CloakTypeClass::DataEntry::Get(AbstractTypeClass* pAbsType)
{
	if (auto* pExtType = TechnoTypeExt::ExtMap.Find(abstract_cast<TechnoTypeExt::base_type*>(pAbsType)))
		return &pExtType->Cloak;
	if (auto* pExtType = BulletTypeExt::ExtMap.Find(abstract_cast<BulletTypeExt::base_type*>(pAbsType)))
		return &pExtType->Cloak;
	if (auto* pExtType = WarheadTypeExt::ExtMap.Find(abstract_cast<WarheadTypeExt::base_type*>(pAbsType)))
		return &pExtType->Cloak;
	return nullptr;
}

void CloakTypeClass::DataEntry::LoadFromINI(CCINIClass* pINI, const char* pSection)
{
	INI_EX exINI(pINI);

	Types.Read(exINI, pSection, "Cloak.Types");
	Radiuses.Read(exINI, pSection, "Cloak.Radiuses");

	Warn.Read(exINI, pSection, "Cloak.Warn");

	IsEnabled =
		Types.HasValue() && Radiuses.HasValue() &&
		!Types.empty() && Radiuses.empty() &&
		Types.size() == Radiuses.size();
	if (!IsEnabled && (Types.HasValue() || Radiuses.HasValue()))
		Debug::Log("[Phobos] Cloak on <%s> disabled because some properties is incorrect. \n", pSection);
}

#pragma region(save/load)

template <class T>
bool CloakTypeClass::DataEntry::Serialize(T& stm)
{
	return stm
		.Process(this->OwnerType)
		.Process(this->Types)
		.Process(this->Radiuses)
		.Process(this->Warn)
		.Success();
}

bool CloakTypeClass::DataEntry::Load(PhobosStreamReader& stm, bool registerForChange)
{
	return this->Serialize(stm);
}

bool CloakTypeClass::DataEntry::Save(PhobosStreamWriter& stm) const
{
	return const_cast<CloakTypeClass::DataEntry*>(this)->Serialize(stm);
}

#pragma endregion(save/load)
