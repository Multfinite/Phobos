#pragma once

#include <AITriggerTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<AITriggerTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(AITriggerTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AITriggerTypeClass> : public AITriggerTypeClass
{
	__PROXY_BODY(AITriggerTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

