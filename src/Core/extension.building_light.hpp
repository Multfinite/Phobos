#pragma once

#include <BuildingLightClass.h>

#include "extension.object.hpp"

template<> class Extension<BuildingLightClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(BuildingLightClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BuildingLightClass> : public ObjectClass
{
	__PROXY_BODY(BuildingLightClass)
	__PROXY_MEMORY_MANAGEMENT
};

