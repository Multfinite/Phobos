#pragma once

#include <VoxelAnimTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<VoxelAnimTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(VoxelAnimTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<VoxelAnimTypeClass> : public VoxelAnimTypeClass
{
	__PROXY_BODY(VoxelAnimTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

