#include "Body.hpp"

#include <Common/AreaAffection.Post.hpp>

__CellExt_ExtData::__CellExt_ExtData(CellClass* ownerObject) : Extension<CellClass>(ownerObject)
	, AreaAffection { new AreaAffection::InstanceEntry(ownerObject) }
	, AreaAffectionCache { new AreaAffection::CellEntry() }
{ }
__CellExt_ExtData::~__CellExt_ExtData()
{
	delete AreaAffection;
	delete AreaAffectionCache;
}

void CellExt::ExtData::LoadFromINIFile(CCINIClass* pINI) {}
void CellExt::ExtData::LoadBeforeTypeData(RulesClass* pThis, CCINIClass* pINI) { }
void CellExt::ExtData::LoadAfterTypeData(RulesClass* pThis, CCINIClass* pINI) { }
void CellExt::ExtData::InitializeConstants() { }
void CellExt::ExtData::InitializeAfterTypeData(RulesClass* pThis) { }

void CellExt::ExtData::InvalidatePointer(void* ptr, bool bRemoved){ }

void CellExt::ExtData::LoadFromStream(PhobosStreamReader& Stm)
{
	Serialize(Stm);
}
void CellExt::ExtData::SaveToStream(PhobosStreamWriter& Stm)
{
	Serialize(Stm);
}

bool CellExt::LoadGlobals(PhobosStreamReader& Stm) { return true; }
bool CellExt::SaveGlobals(PhobosStreamWriter& Stm) { return true; }

// =============================
// container

CellExt::ExtContainer CellExt::ExtMap;

CellExt::ExtContainer::ExtContainer() : Container("CellClass") { }
CellExt::ExtContainer::~ExtContainer() = default;

// =============================
// container hooks

// Notice: NO VTABLES on CellClass present Here
DEFINE_HOOK(0x47B389, CellClass_CTOR_NoInit, 0x7)
{
	GET(CellClass*, pItem, ESI);

	CellExt::ExtMap.TryAllocate(pItem);

	return 0;
}
DEFINE_HOOK(0x47BDA1, CellClass_CTOR, 0x6)
{
	GET(CellClass*, pItem, ESI);

	CellExt::ExtMap.TryAllocate(pItem);

	return 0;
}

DEFINE_HOOK(0x47BB60, CellClass_DTOR, 0x6)
{
	GET(CellClass*, pItem, ECX);

	CellExt::ExtMap.Remove(pItem);

	return 0;
}

DEFINE_HOOK_AGAIN(0x4839F0, CellClass_SaveLoad_Prefix, 0x5)
DEFINE_HOOK(0x483C10, CellClass_SaveLoad_Prefix, 0x5)
{
	GET_STACK(CellClass*, pItem, 0x4);
	GET_STACK(IStream*, pStm, 0x8);

	CellExt::ExtMap.PrepareStream(pItem, pStm);

	return 0;
}

DEFINE_HOOK(0x483C00, CellClass_Load_Suffix, 0x5)
{
	CellExt::ExtMap.LoadStatic();

	return 0;
}

DEFINE_HOOK(0x483C79, CellClass_Save_Suffix, 0x5)
{
	CellExt::ExtMap.SaveStatic();

	return 0;
}

