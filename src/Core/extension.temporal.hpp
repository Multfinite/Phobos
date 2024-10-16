#pragma once

#include <TemporalClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TemporalClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TemporalClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TemporalClass> : public TemporalClass
{
	__PROXY_BODY(TemporalClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TemporalClass>>
{
	using type = Extension<TemporalClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TemporalClass)
