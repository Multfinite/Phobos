#pragma once

#include <Timer.h>
#include <vector>

#include <AbstractClass.h>

#include <Utilities/Enumerable.h>
#include <Utilities/Template.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>
#include <Utilities/TemplateDef.h>

#include <Common/AreaAffection.hpp>

#include <New/Type/CloakTypeClass.hpp>
#include <New/Type/SensorTypeClass.hpp>

class SensorClass : public AreaAffection::Instance<SensorTypeClass, AreaAffection::DataEntry<SensorClass>>
{
public:
	void In(__CellExt_ExtData& cell, short radius, int radiusSq) override;
	void Out(__CellExt_ExtData& cell, short radius, int radiusSq) override;

	SensorClass(SensorTypeClass* type, AbstractClass* parent, HouseClass* owner, short radius) : Instance(type, parent, owner, radius) {}
};

static_assert(AreaAffection::IsInstance<SensorClass>, "It is not a Area Affection!");
