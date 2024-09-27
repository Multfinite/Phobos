#pragma once

#include <TemporalClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TemporalClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TemporalClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TemporalClass> : public AbstractClass
{
	__PROXY_BODY(TemporalClass)
	__PROXY_MEMORY_MANAGEMENT
};

