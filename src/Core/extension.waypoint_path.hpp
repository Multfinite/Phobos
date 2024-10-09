#pragma once

#include <WaypointPathClass.h>

#include "extension.abstract.hpp"

template<> class Extension<WaypointPathClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(WaypointPathClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<WaypointPathClass> : public WaypointPathClass
{
	__PROXY_BODY(WaypointPathClass)
	__PROXY_MEMORY_MANAGEMENT
};

