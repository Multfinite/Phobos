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

#include <New/Type/ElectronicWarfareTypeClass.hpp>

class ElectronicWarfareClass : public AreaAffection::Instance<ElectronicWarfareTypeClass, AreaAffection::DataEntry<ElectronicWarfareClass>>
{
public:
	void In(__CellExt_ExtData& cell, short radius, int radiusSq) override;
	void Out(__CellExt_ExtData& cell, short radius, int radiusSq) override;

	ElectronicWarfareClass(ElectronicWarfareTypeClass* type, AbstractClass* parent, HouseClass* owner, short radius) : Instance(type, parent, owner, radius) { }
};

static_assert(AreaAffection::IsInstance<ElectronicWarfareClass>, "It is not a Area Affection!");
