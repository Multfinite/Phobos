#pragma once

#include <LightSourceClass.h>

#include "extension.abstract.hpp"

template<> class Extension<LightSourceClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(LightSourceClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<LightSourceClass> : public LightSourceClass
{
	__PROXY_BODY(LightSourceClass)
	__PROXY_MEMORY_MANAGEMENT
};

