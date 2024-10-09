#pragma once

#include <SpawnManagerClass.h>

#include "extension.abstract.hpp"

template<> class Extension<SpawnManagerClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(SpawnManagerClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SpawnManagerClass> : public SpawnManagerClass
{
	__PROXY_BODY(SpawnManagerClass)
	__PROXY_MEMORY_MANAGEMENT
};

