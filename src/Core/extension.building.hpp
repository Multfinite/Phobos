#pragma once

#include <BuildingClass.h>

#include "extension.techno.hpp"

template<> class Extension<BuildingClass> : public Extension<TechnoClass>
{
	__EXTENSION_BODY(BuildingClass, Extension<TechnoClass>::Offset)
public:
	using parent_type = Extension<TechnoClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BuildingClass> : public BuildingClass
{
	__PROXY_BODY(BuildingClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<BuildingClass>>
{
	using type = Extension<BuildingClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(BuildingClass)
