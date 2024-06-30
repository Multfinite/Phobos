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

class CloakClass : public AreaAffection::Instance<CloakClass, CloakTypeClass, AreaAffection::DataEntry<CloakClass>>
{
public:
	using typed_instance = AreaAffection::Instance<CloakClass, CloakTypeClass, AreaAffection::DataEntry<CloakClass>>;

	static std::list<CloakClass*> Array;

	void In(__CellExt_ExtData& cell, short radius, int radiusSq) override;
	void Out(__CellExt_ExtData& cell, short radius, int radiusSq) override;

	CloakClass(CloakTypeClass* type, AbstractClass* parent, HouseClass* owner, short radius) : Instance(type, parent, owner, radius) { }
};

static_assert(AreaAffection::IsInstance<CloakClass>, "It is not a Area Affection!");
