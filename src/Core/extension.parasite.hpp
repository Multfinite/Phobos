#pragma once

#include <ParasiteClass.h>

#include "extension.abstract.hpp"

template<> class Extension<ParasiteClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(ParasiteClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ParasiteClass> : public ParasiteClass
{
	__PROXY_BODY(ParasiteClass)
	__PROXY_MEMORY_MANAGEMENT
};

