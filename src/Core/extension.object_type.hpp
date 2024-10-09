#pragma once

#include <ObjectTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<ObjectTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(ObjectTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ObjectTypeClass> : public ObjectTypeClass
{
	__PROXY_BODY(ObjectTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

