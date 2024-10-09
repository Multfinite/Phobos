#pragma once

#include <TiberiumClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<TiberiumClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(TiberiumClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TiberiumClass> : public TiberiumClass
{
	__PROXY_BODY(TiberiumClass)
	__PROXY_MEMORY_MANAGEMENT
};

