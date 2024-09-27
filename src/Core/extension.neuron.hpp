#pragma once

#include <NeuronClass.h>

#include "extension.abstract.hpp"

template<> class Extension<NeuronClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(NeuronClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<NeuronClass> : public AbstractClass
{
	__PROXY_BODY(NeuronClass)
	__PROXY_MEMORY_MANAGEMENT
};

