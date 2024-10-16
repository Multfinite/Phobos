#pragma once

#include <WeaponTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<WeaponTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(WeaponTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<WeaponTypeClass> : public WeaponTypeClass
{
	__PROXY_BODY(WeaponTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<WeaponTypeClass>>
{
	using type = Extension<WeaponTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(WeaponTypeClass)
