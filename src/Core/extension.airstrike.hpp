#pragma once

#include <AirstrikeClass.h>

#include "extension.abstract.hpp"

template<> class Extension<AirstrikeClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(AirstrikeClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AirstrikeClass> : public AbstractClass
{
	__PROXY_BODY(AirstrikeClass)
	__PROXY_MEMORY_MANAGEMENT
};

