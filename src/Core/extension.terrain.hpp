#pragma once

#include <TerrainClass.h>

#include "extension.object.hpp"

template<> class Extension<TerrainClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(TerrainClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TerrainClass> : public TerrainClass
{
	__PROXY_BODY(TerrainClass)
	__PROXY_MEMORY_MANAGEMENT
};

