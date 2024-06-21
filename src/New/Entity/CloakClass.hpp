#pragma once

#include <Timer.h>
#include <vector>;

#include <AbstractClass.h>

#include <Utilities/Enumerable.h>
#include <Utilities/Template.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>
#include <Utilities/TemplateDef.h>

#include <Common/AreaAffection.Body.hpp>

#include <New/Type/CloakTypeClass.hpp>

using CloakClass = AreaAffection::Instance<CloakTypeClass>;

static_assert(AreaAffection::IsAreaAffection<CloakClass>, "It is not a Area Affection!");
