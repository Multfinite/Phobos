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

template<> struct Proxy<ParticleSystemClass> : public ParticleSystemClass
{
	__PROXY_BODY(ParticleSystemClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<ParticleSystemClass>>
{
	using type = Extension<ParticleSystemClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ParticleSystemClass)
