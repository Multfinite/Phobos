#pragma once

#include <EMPulseClass.h>

#include "extension.abstract.hpp"

template<> class Extension<EMPulseClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(EMPulseClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<EMPulseClass> : public EMPulseClass
{
	__PROXY_BODY(EMPulseClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<EMPulseClass>>
{
	using type = Extension<EMPulseClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(EMPulseClass)
