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

template<> struct Proxy<ParticleClass> : public ParticleClass
{
	__PROXY_BODY(ParticleClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<ParticleClass>>
{
	using type = Extension<ParticleClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ParticleClass)
