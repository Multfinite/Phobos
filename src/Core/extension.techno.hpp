#pragma once

#include <TechnoClass.h>

#include "extension.radio.hpp"

template<> class Extension<TechnoClass> : public Extension<RadioClass>
{
	__EXTENSION_BODY(TechnoClass, Extension<RadioClass>::Offset)
public:
	using parent_type = Extension<RadioClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TechnoClass> : public TechnoClass
{
	__PROXY_BODY(TechnoClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TechnoClass>>
{
	using type = Extension<TechnoClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TechnoClass)
