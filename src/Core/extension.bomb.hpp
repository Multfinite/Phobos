#pragma once

#include <BombClass.h>

#include "extension.abstract.hpp"

template<> class Extension<BombClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(BombClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BombClass> : public BombClass
{
	__PROXY_BODY(BombClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<BombClass>>
{
	using type = Extension<BombClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(BombClass)
