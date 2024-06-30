#include "ElectronicWarfareClass.hpp"

#include <MapClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/Cell/Body.hpp>

#include <Common/AreaAffection.Body.hpp>
#include <Common/AreaAffection.Post.hpp>

decltype(AreaAffection::Logic<ElectronicWarfareClass::typed_instance>::Instance) AreaAffection::Logic<ElectronicWarfareClass::typed_instance>::Instance;
decltype(AreaAffection::Logic<ElectronicWarfareClass>::Instance) AreaAffection::Logic<ElectronicWarfareClass>::Instance;
decltype(ElectronicWarfareClass::Array) ElectronicWarfareClass::Array;

void ElectronicWarfareClass::In(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Register(this);
}
void ElectronicWarfareClass::Out(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Unregister(this);
}
