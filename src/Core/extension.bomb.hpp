#pragma once

#include <BombClass.h>

#include "extension.abstract.hpp"

template<> class Extension<BombClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(BombClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BombClass> : public BombClass
{
	__PROXY_BODY(BombClass)
	__PROXY_MEMORY_MANAGEMENT
};

