#pragma once

#include <FactoryClass.h>

#include "extension.abstract.hpp"

template<> class Extension<FactoryClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(FactoryClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<FactoryClass> : public FactoryClass
{
	__PROXY_BODY(FactoryClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<FactoryClass>>
{
	using type = Extension<FactoryClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(FactoryClass)
