#pragma once

#include <SuperWeaponTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<SuperWeaponTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(SuperWeaponTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SuperWeaponTypeClass> : public SuperWeaponTypeClass
{
	__PROXY_BODY(SuperWeaponTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<SuperWeaponTypeClass>>
{
	using type = Extension<SuperWeaponTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(SuperWeaponTypeClass)
