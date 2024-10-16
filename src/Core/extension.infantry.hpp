#pragma once

#include <InfantryClass.h>

#include "extension.foot.hpp"

template<> class Extension<InfantryClass> : public Extension<FootClass>
{
	__EXTENSION_BODY(InfantryClass, Extension<FootClass>::Offset)
public:
	using parent_type = Extension<FootClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<InfantryClass> : public InfantryClass
{
	__PROXY_BODY(InfantryClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<InfantryClass>>
{
	using type = Extension<InfantryClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(InfantryClass)
