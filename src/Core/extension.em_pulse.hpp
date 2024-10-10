#pragma once

#include <EMPulseClass.h>

#include "extension.abstract.hpp"

template<> class Extension<EMPulseClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(EMPulseClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<EMPulseClass> : public AbstractClass
{
	__PROXY_BODY(EMPulseClass)
	__PROXY_MEMORY_MANAGEMENT
};

