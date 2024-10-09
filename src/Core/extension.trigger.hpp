#pragma once

#include <TriggerClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TriggerClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TriggerClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TriggerClass> : public TriggerClass
{
	__PROXY_BODY(TriggerClass)
	__PROXY_MEMORY_MANAGEMENT
};

