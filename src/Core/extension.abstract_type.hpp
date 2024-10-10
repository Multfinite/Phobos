#pragma once

#include <AbstractTypeClass.h>

#include "extension.abstract.hpp"

template<> class Extension<AbstractTypeClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(AbstractTypeClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AbstractTypeClass> : public AbstractClass
{
	__PROXY_BODY(AbstractTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

