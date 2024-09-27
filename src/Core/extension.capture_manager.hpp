#pragma once

#include <CaptureManagerClass.h>

#include "extension.abstract.hpp"

template<> class Extension<CaptureManagerClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(CaptureManagerClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<CaptureManagerClass> : public AbstractClass
{
	__PROXY_BODY(CaptureManagerClass)
	__PROXY_MEMORY_MANAGEMENT
};

