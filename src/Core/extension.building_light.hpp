#pragma once

#include <BuildingLightClass.h>

#include "extension.object.hpp"

template<> class Extension<BuildingLightClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(BuildingLightClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BuildingLightClass> : public BuildingLightClass
{
	__PROXY_BODY(BuildingLightClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<BuildingLightClass>>
{
	using type = Extension<BuildingLightClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(BuildingLightClass)
