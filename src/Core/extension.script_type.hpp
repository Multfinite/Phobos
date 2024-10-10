#pragma once

#include <ScriptTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<ScriptTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(ScriptTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ScriptTypeClass> : public AbstractTypeClass
{
	__PROXY_BODY(ScriptTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

