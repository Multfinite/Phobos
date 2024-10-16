#pragma once

#include <LightSourceClass.h>

#include "extension.abstract.hpp"

template<> class Extension<LightSourceClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(LightSourceClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<LightSourceClass> : public LightSourceClass
{
	__PROXY_BODY(LightSourceClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<LightSourceClass>>
{
	using type = Extension<LightSourceClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(LightSourceClass)
