#pragma once

#include <AbstractTypeClass.h>

#include "extension.abstract.hpp"

template<> class Extension<AbstractTypeClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(AbstractTypeClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AbstractTypeClass> : public AbstractTypeClass
{
	__PROXY_BODY(AbstractTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AbstractTypeClass>>
{
	using type = Extension<AbstractTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AbstractTypeClass)
