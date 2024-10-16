#pragma once

#include <TacticalClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TacticalClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TacticalClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TacticalClass> : public TacticalClass
{
	__PROXY_BODY(TacticalClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TacticalClass>>
{
	using type = Extension<TacticalClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TacticalClass)
