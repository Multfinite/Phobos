#pragma once

#include <BulletTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<BulletTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(BulletTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BulletTypeClass> : public BulletTypeClass
{
	__PROXY_BODY(BulletTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

