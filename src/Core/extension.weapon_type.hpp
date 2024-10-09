#pragma once

#include <WeaponTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<WeaponTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(WeaponTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<WeaponTypeClass> : public WeaponTypeClass
{
	__PROXY_BODY(WeaponTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

