#pragma once

#include <TacticalClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TacticalClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TacticalClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TacticalClass> : public AbstractClass
{
	__PROXY_BODY(TacticalClass)
	__PROXY_MEMORY_MANAGEMENT
};

