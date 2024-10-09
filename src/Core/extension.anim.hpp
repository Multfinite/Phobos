#pragma once

#include <AnimClass.h>

#include "extension.object.hpp"

template<> class Extension<AnimClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(AnimClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AnimClass> : public AnimClass
{
	__PROXY_BODY(AnimClass)
	__PROXY_MEMORY_MANAGEMENT
};

