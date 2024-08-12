#include "SensorClass.hpp"

#include <MapClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/Cell/Body.hpp>

#include <Common/AreaAffection.Body.hpp>
#include <Common/AreaAffection.Post.hpp>

decltype(SensorClass::logic::Instance) SensorClass::logic::Instance;
decltype(SensorClass::Array) SensorClass::Array;

void SensorClass::In(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Register(this);
}
void SensorClass::Out(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Unregister(this);
}
