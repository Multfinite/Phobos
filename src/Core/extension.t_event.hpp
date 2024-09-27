#pragma once

#include <TEventClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TEventClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TEventClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TEventClass> : public AbstractClass
{
	__PROXY_BODY(TEventClass)
	__PROXY_MEMORY_MANAGEMENT
};

