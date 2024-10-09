#pragma once

#include <TagTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<TagTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(TagTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TagTypeClass> : public TagTypeClass
{
	__PROXY_BODY(TagTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

