#pragma once

#include <HouseClass.h>

#include "extension.abstract.hpp"

template<> class Extension<HouseClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(HouseClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<HouseClass> : public HouseClass
{
	__PROXY_BODY(HouseClass)
	__PROXY_MEMORY_MANAGEMENT
};

