#pragma once

#include <UnitClass.h>

#include "extension.foot.hpp"

template<> class Extension<UnitClass> : public Extension<FootClass>
{
	__EXTENSION_BODY(UnitClass, Extension<FootClass>::Offset)
public:
	using parent_type = Extension<FootClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<UnitClass> : public UnitClass
{
	__PROXY_BODY(UnitClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<UnitClass>>
{
	using type = Extension<UnitClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(UnitClass)
