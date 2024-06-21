#include "CloakClass.hpp"

#include <MapClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/Cell/Body.hpp>

void CloakClass::In(CellExt::ExtData* cellExt, short radius, int radiusSq)
{
	cellExt->AreaAffectionCache.Register(this);
}
void CloakClass::Out(CellExt::ExtData* cellExt, short radius, int radiusSq)
{
	cellExt->AreaAffectionCache.Unregister(this);
}
