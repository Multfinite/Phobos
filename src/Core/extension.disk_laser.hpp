#pragma once

#include <DiskLaserClass.h>

#include "extension.abstract.hpp"

template<> class Extension<DiskLaserClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(DiskLaserClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<DiskLaserClass> : public DiskLaserClass
{
	__PROXY_BODY(DiskLaserClass)
	__PROXY_MEMORY_MANAGEMENT
};

