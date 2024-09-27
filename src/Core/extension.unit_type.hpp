#pragma once

#include <UnitTypeClass.h>

#include "extension.techno_type.hpp"

template<> class Extension<UnitTypeClass> : public Extension<TechnoTypeClass>
{
	__EXTENSION_BODY(UnitTypeClass, Extension<TechnoTypeClass>::Offset)
public:
	using parent_type = Extension<TechnoTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<UnitTypeClass> : public TechnoTypeClass
{
	__PROXY_BODY(UnitTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

