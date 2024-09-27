#pragma once

#include <ObjectClass.h>

#include "extension.abstract.hpp"

template<> class Extension<ObjectClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(ObjectClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ObjectClass> : public AbstractClass
{
	__PROXY_BODY(ObjectClass)
	__PROXY_MEMORY_MANAGEMENT
};

