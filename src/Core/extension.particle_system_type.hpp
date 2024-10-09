#pragma once

#include <ParticleSystemTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<ParticleSystemTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(ParticleSystemTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ParticleSystemTypeClass> : public ParticleSystemTypeClass
{
	__PROXY_BODY(ParticleSystemTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

