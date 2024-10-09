#pragma once

#include <WaveClass.h>

#include "extension.object.hpp"

template<> class Extension<WaveClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(WaveClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<WaveClass> : public WaveClass
{
	__PROXY_BODY(WaveClass)
	__PROXY_MEMORY_MANAGEMENT
};

