#pragma once

#include <AircraftTypeClass.h>

#include "extension.techno_type.hpp"

template<> class Extension<AircraftTypeClass> : public Extension<TechnoTypeClass>
{
	__EXTENSION_BODY(AircraftTypeClass, Extension<TechnoTypeClass>::Offset)
public:
	using parent_type = Extension<TechnoTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AircraftTypeClass> : public TechnoTypeClass
{
	__PROXY_BODY(AircraftTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

