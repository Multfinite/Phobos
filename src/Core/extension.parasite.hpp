#pragma once

#include <ParasiteClass.h>

#include "extension.abstract.hpp"

template<> class Extension<ParasiteClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(ParasiteClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ParasiteClass> : public ParasiteClass
{
	__PROXY_BODY(ParasiteClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<ParasiteClass>>
{
	using type = Extension<ParasiteClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ParasiteClass)
