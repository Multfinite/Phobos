#pragma once

#include <WaypointPathClass.h>

#include "extension.abstract.hpp"

template<> class Extension<WaypointPathClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(WaypointPathClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<WaypointPathClass> : public WaypointPathClass
{
	__PROXY_BODY(WaypointPathClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<WaypointPathClass>>
{
	using type = Extension<WaypointPathClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(WaypointPathClass)
