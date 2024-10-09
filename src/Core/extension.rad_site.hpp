#pragma once

#include <RadSiteClass.h>

#include "extension.abstract.hpp"

template<> class Extension<RadSiteClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(RadSiteClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<RadSiteClass> : public RadSiteClass
{
	__PROXY_BODY(RadSiteClass)
	__PROXY_MEMORY_MANAGEMENT
};

