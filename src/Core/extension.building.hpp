#pragma once

#include <BuildingClass.h>

#include "extension.techno.hpp"

template<> class Extension<BuildingClass> : public Extension<TechnoClass>
{
	__EXTENSION_BODY(BuildingClass, Extension<TechnoClass>::Offset)
public:
	using parent_type = Extension<TechnoClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BuildingClass> : public TechnoClass
{
	__PROXY_BODY(BuildingClass)
	__PROXY_MEMORY_MANAGEMENT
};

