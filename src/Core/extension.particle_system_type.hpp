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

template<> struct Formatter<Extension<ParticleSystemTypeClass>>
{
	using type = Extension<ParticleSystemTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ParticleSystemTypeClass)
