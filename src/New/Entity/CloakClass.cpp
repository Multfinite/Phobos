#include "CloakClass.hpp"

#include <MapClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/Cell/Body.hpp>

#include <Common/AreaAffection.Body.hpp>
#include <Common/AreaAffection.Post.hpp>

decltype(CloakClass::logic::Instance) CloakClass::logic::Instance;
decltype(CloakClass::Array) CloakClass::Array;

void CloakClass::In(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Register(this);
}
void CloakClass::Out(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Unregister(this);
}


void CloakClassDataEntry::__on_instantiate(instance* pInst)
{
	base_type::__on_instantiate(pInst);

	ByCloakType[pInst->Type->Type].push_back(pInst);
}
void CloakClassDataEntry::__on_deinstantiate(instance* pInst)
{
	base_type::__on_deinstantiate(pInst);

	ByCloakType[pInst->Type->Type].remove(pInst);
}
