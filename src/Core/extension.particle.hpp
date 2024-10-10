#pragma once

#include <ParticleClass.h>

#include "extension.object.hpp"

template<> class Extension<ParticleClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(ParticleClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ParticleClass> : public ObjectClass
{
	__PROXY_BODY(ParticleClass)
	__PROXY_MEMORY_MANAGEMENT
};

