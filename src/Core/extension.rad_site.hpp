#pragma once

#include <RadSiteClass.h>

#include "extension.abstract.hpp"

template<> class Extension<RadSiteClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(RadSiteClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<RadSiteClass> : public RadSiteClass
{
	__PROXY_BODY(RadSiteClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<RadSiteClass>>
{
	using type = Extension<RadSiteClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(RadSiteClass)
