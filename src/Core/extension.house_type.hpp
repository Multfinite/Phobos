#pragma once

#include <HouseTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<HouseTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(HouseTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<HouseTypeClass> : public HouseTypeClass
{
	__PROXY_BODY(HouseTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<HouseTypeClass>>
{
	using type = Extension<HouseTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(HouseTypeClass)
