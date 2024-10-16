#pragma once

#include <TActionClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TActionClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TActionClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TActionClass> : public TActionClass
{
	__PROXY_BODY(TActionClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TActionClass>>
{
	using type = Extension<TActionClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TActionClass)
