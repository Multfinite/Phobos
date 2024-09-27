#pragma once

#include <ScriptClass.h>

#include "extension.abstract.hpp"

template<> class Extension<ScriptClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(ScriptClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ScriptClass> : public AbstractClass
{
	__PROXY_BODY(ScriptClass)
	__PROXY_MEMORY_MANAGEMENT
};

