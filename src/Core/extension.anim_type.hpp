#pragma once

#include <AnimTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<AnimTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(AnimTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AnimTypeClass> : public AnimTypeClass
{
	__PROXY_BODY(AnimTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AnimTypeClass>>
{
	using type = Extension<AnimTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AnimTypeClass)
