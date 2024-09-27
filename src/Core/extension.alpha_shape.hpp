#pragma once

#include <AlphaShapeClass.h>

#include "extension.abstract.hpp"

template<> class Extension<AlphaShapeClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(AlphaShapeClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AlphaShapeClass> : public AbstractClass
{
	__PROXY_BODY(AlphaShapeClass)
	__PROXY_MEMORY_MANAGEMENT
};

