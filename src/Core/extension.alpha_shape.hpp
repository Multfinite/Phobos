#pragma once

#include <AlphaShapeClass.h>

#include "extension.abstract.hpp"

template<> class Extension<AlphaShapeClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(AlphaShapeClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AlphaShapeClass> : public AlphaShapeClass
{
	__PROXY_BODY(AlphaShapeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AlphaShapeClass>>
{
	using type = Extension<AlphaShapeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AlphaShapeClass)
