#pragma once

#include <VeinholeMonsterClass.h>

#include "extension.object.hpp"

template<> class Extension<VeinholeMonsterClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(VeinholeMonsterClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<VeinholeMonsterClass> : public ObjectClass
{
	__PROXY_BODY(VeinholeMonsterClass)
	__PROXY_MEMORY_MANAGEMENT
};

