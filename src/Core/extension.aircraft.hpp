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

template<> struct Proxy<AircraftClass> : public FootClass
{
	__PROXY_BODY(AircraftClass)
	__PROXY_MEMORY_MANAGEMENT
};

