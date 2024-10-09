#pragma once

#include <SideClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<SideClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(SideClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SideClass> : public SideClass
{
	__PROXY_BODY(SideClass)
	__PROXY_MEMORY_MANAGEMENT
};

