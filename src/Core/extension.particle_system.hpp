#pragma once

#include <ParticleSystemClass.h>

#include "extension.object.hpp"

template<> class Extension<ParticleSystemClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(ParticleSystemClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ParticleSystemClass> : public ObjectClass
{
	__PROXY_BODY(ParticleSystemClass)
	__PROXY_MEMORY_MANAGEMENT
};

