#pragma once

#include <InfantryClass.h>

#include "extension.foot.hpp"

template<> class Extension<InfantryClass> : public Extension<FootClass>
{
	__EXTENSION_BODY(InfantryClass, Extension<FootClass>::Offset)
public:
	using parent_type = Extension<FootClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<InfantryClass> : public InfantryClass
{
	__PROXY_BODY(InfantryClass)
	__PROXY_MEMORY_MANAGEMENT
};

