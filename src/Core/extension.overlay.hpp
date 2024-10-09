#pragma once

#include <OverlayClass.h>

#include "extension.object.hpp"

template<> class Extension<OverlayClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(OverlayClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<OverlayClass> : public OverlayClass
{
	__PROXY_BODY(OverlayClass)
	__PROXY_MEMORY_MANAGEMENT
};

