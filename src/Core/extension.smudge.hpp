#pragma once

#include <SmudgeClass.h>

#include "extension.object.hpp"

template<> class Extension<SmudgeClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(SmudgeClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SmudgeClass> : public ObjectClass
{
	__PROXY_BODY(SmudgeClass)
	__PROXY_MEMORY_MANAGEMENT
};

