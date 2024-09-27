#include "SensorClass.hpp"

#include <MapClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/Bullet/Body.h>
#include <Ext/Cell/Body.hpp>

#include <Common/AreaAffection.Body.hpp>
#include <Common/AreaAffection.Post.hpp>

decltype(AreaAffection::Logic<SensorClass>::Instance) AreaAffection::Logic<SensorClass>::Instance;
decltype(SensorClass::Array) SensorClass::Array;

void SensorClass::In(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Register(this);
}
void SensorClass::Out(__CellExt_ExtData& cellExt, short radius, int radiusSq)
{
	cellExt.AreaAffectionCache->Unregister(this);
}

SensorClass::SensorClass(SensorTypeClass* type, class AbstractClass* parent, HouseClass* owner, short radius) : Instance(parent, owner, radius)
, Type(type)
{
	Array.push_back(this);
}
SensorClass::~SensorClass()
{
	if (ClearedByEntry) return;
	AreaAffection::Logic<SensorClass>::Instance.ClearInstance(this);
}
