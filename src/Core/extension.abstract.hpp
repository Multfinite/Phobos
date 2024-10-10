#pragma once

#include <AbstractClass.h>

#include "core.extensions.hpp"

template<> class Extension<AbstractClass> : public IExtension
{
	__EXTENSION_BODY(AbstractClass, 0x18)
public:
	using parent_type = IExtension;
protected:
	constexpr Extension(base_type& base) : IExtension(&base) { }
};

template<> struct Proxy<AbstractClass> : public AbstractClass
{
	__PROXY_BODY(AbstractClass)
	__PROXY_MEMORY_MANAGEMENT
};
