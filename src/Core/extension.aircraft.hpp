#pragma once

#include <AircraftClass.h>

#include "extension.foot.hpp"

template<> class Extension<AircraftClass> : public Extension<FootClass>
{
	__EXTENSION_BODY(AircraftClass, Extension<FootClass>::Offset)
public:
	using parent_type = Extension<FootClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AircraftClass> : public AircraftClass
{
	__PROXY_BODY(AircraftClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AircraftClass>>
{
	using type = Extension<AircraftClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AircraftClass)
