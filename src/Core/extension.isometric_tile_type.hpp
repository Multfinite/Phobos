#pragma once

#include <IsometricTileTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<IsometricTileTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(IsometricTileTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<IsometricTileTypeClass> : public IsometricTileTypeClass
{
	__PROXY_BODY(IsometricTileTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

