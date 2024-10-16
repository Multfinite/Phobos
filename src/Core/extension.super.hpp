#pragma once

#include <SuperClass.h>

#include "extension.abstract.hpp"

template<> class Extension<SuperClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(SuperClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SuperClass> : public SuperClass
{
	__PROXY_BODY(SuperClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<SuperClass>>
{
	using type = Extension<SuperClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(SuperClass)
