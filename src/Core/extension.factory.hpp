#pragma once

#include <FactoryClass.h>

#include "extension.abstract.hpp"

template<> class Extension<FactoryClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(FactoryClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<FactoryClass> : public AbstractClass
{
	__PROXY_BODY(FactoryClass)
	__PROXY_MEMORY_MANAGEMENT
};

