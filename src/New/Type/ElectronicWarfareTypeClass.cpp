#include "ElectronicWarfareTypeClass.hpp"

#include <Ext/TechnoType/Body.h>
#include <Ext/BulletType/Body.h>
#include <Ext/WarheadType/Body.h>

#include <Common/AreaAffection.Post.hpp>
#include <Common/Entry.Impl.hpp>

template<> const char* Enumerable<ElectronicWarfareTypeClass>::GetMainSection() { return "EWTypes"; }

void data_entry<ElectronicWarfareTypeClass>::LoadFromINI(CCINIClass* pINI, const char* pSection)
{
	INI_EX exINI(pINI);
}

#pragma region(save/load)

template <class T>
bool data_entry<ElectronicWarfareTypeClass>::Serialize(T& stm)
{
	return stm
		.Process(this->OwnerType)
		.Success();
}

bool data_entry<ElectronicWarfareTypeClass>::Load(PhobosStreamReader& stm, bool registerForChange)
{
	return this->Serialize(stm);
}

bool data_entry<ElectronicWarfareTypeClass>::Save(PhobosStreamWriter& stm) const
{
	return const_cast<data_entry<ElectronicWarfareTypeClass>*>(this)->Serialize(stm);
}

#pragma endregion(save/load)
