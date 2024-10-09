#pragma once

#include <VoxelAnimClass.h>

#include "extension.object.hpp"

template<> class Extension<VoxelAnimClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(VoxelAnimClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<VoxelAnimClass> : public VoxelAnimClass
{
	__PROXY_BODY(VoxelAnimClass)
	__PROXY_MEMORY_MANAGEMENT
};

