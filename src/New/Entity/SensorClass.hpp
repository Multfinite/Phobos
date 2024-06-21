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
#include <New/Type/SensorTypeClass.hpp>

using SensorClass = AreaAffection::Instance<SensorTypeClass>;

static_assert(AreaAffection::IsAreaAffection<SensorClass>, "It is not a Area Affection!");
