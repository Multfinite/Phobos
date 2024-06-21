#include "SensorClass.hpp"

#include <MapClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/Cell/Body.hpp>

void SensorClass::In(CellExt::ExtData* cellExt, short radius, int radiusSq)
{
	cellExt->AreaAffectionCache.Register(this);
}
void SensorClass::Out(CellExt::ExtData* cellExt, short radius, int radiusSq)
{
	cellExt->AreaAffectionCache.Unregister(this);
}
