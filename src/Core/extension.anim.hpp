#pragma once

#include <AnimClass.h>

#include "extension.object.hpp"

template<> class Extension<AnimClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(AnimClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AnimClass> : public AnimClass
{
	__PROXY_BODY(AnimClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AnimClass>>
{
	using type = Extension<AnimClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AnimClass)
