#pragma once

#include <AirstrikeClass.h>

#include "extension.abstract.hpp"

template<> class Extension<AirstrikeClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(AirstrikeClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<AirstrikeClass> : public AirstrikeClass
{
	__PROXY_BODY(AirstrikeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AirstrikeClass>>
{
	using type = Extension<AirstrikeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AirstrikeClass)
