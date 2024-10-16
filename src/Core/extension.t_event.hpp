#pragma once

#include <TEventClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TEventClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TEventClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TEventClass> : public TEventClass
{
	__PROXY_BODY(TEventClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TEventClass>>
{
	using type = Extension<TEventClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TEventClass)
