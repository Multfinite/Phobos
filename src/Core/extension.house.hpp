#pragma once

#include <HouseClass.h>

#include "extension.abstract.hpp"

template<> class Extension<HouseClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(HouseClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<HouseClass> : public HouseClass
{
	__PROXY_BODY(HouseClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<HouseClass>>
{
	using type = Extension<HouseClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(HouseClass)
