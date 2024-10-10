#pragma once

#include <ParticleTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<ParticleTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(ParticleTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ParticleTypeClass> : public ObjectTypeClass
{
	__PROXY_BODY(ParticleTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

