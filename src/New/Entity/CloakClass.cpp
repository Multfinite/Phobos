#include "CloakClass.hpp"

#include <MapClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/Cell/Body.hpp>

#include <Common/AreaAffection.Body.hpp>
#include <Common/AreaAffection.Post.hpp>

decltype(AreaAffection::Logic<CloakClass::typed_instance>::Instance) AreaAffection::Logic<CloakClass::typed_instance>::Instance;
decltype(AreaAffection::Logic<CloakClass>::Instance) AreaAffection::Logic<CloakClass>::Instance;
decltype(CloakClass::Array) CloakClass::Array;

void CloakClass::In(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Register(this);
}
void CloakClass::Out(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Unregister(this);
}
