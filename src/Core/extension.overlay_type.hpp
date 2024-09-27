#pragma once

#include <OverlayTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<OverlayTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(OverlayTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<OverlayTypeClass> : public ObjectTypeClass
{
	__PROXY_BODY(OverlayTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

