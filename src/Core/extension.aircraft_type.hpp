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

template<> struct Proxy<AircraftTypeClass> : public AircraftTypeClass
{
	__PROXY_BODY(AircraftTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AircraftTypeClass>>
{
	using type = Extension<AircraftTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AircraftTypeClass)
