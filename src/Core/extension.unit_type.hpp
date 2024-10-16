#pragma once

#include <UnitTypeClass.h>

#include "extension.techno_type.hpp"

template<> class Extension<UnitTypeClass> : public Extension<TechnoTypeClass>
{
	__EXTENSION_BODY(UnitTypeClass, Extension<TechnoTypeClass>::Offset)
public:
	using parent_type = Extension<TechnoTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<UnitTypeClass> : public UnitTypeClass
{
	__PROXY_BODY(UnitTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<UnitTypeClass>>
{
	using type = Extension<UnitTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(UnitTypeClass)
