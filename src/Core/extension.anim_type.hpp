#pragma once

#include <AnimTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<AnimTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(AnimTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AnimTypeClass> : public ObjectTypeClass
{
	__PROXY_BODY(AnimTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

