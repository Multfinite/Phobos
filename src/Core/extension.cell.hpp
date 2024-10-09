#pragma once

#include <CellClass.h>

#include "extension.abstract.hpp"

template<> class Extension<CellClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(CellClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<CellClass> : public CellClass
{
	__PROXY_BODY(CellClass)
	__PROXY_MEMORY_MANAGEMENT
};

