#pragma once

#include <BuildingTypeClass.h>

#include "extension.techno_type.hpp"

template<> class Extension<BuildingTypeClass> : public Extension<TechnoTypeClass>
{
	__EXTENSION_BODY(BuildingTypeClass, Extension<TechnoTypeClass>::Offset)
public:
	using parent_type = Extension<TechnoTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BuildingTypeClass> : public BuildingTypeClass
{
	__PROXY_BODY(BuildingTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

