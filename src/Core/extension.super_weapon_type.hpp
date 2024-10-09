#pragma once

#include <SuperWeaponTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<SuperWeaponTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(SuperWeaponTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SuperWeaponTypeClass> : public SuperWeaponTypeClass
{
	__PROXY_BODY(SuperWeaponTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

