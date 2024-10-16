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

template<> struct Proxy<ParticleTypeClass> : public ParticleTypeClass
{
	__PROXY_BODY(ParticleTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<ParticleTypeClass>>
{
	using type = Extension<ParticleTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ParticleTypeClass)
