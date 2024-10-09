#pragma once

#include <TechnoTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<TechnoTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(TechnoTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TechnoTypeClass> : public TechnoTypeClass
{
	__PROXY_BODY(TechnoTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

