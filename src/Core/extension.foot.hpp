#pragma once

#include <FootClass.h>

#include "extension.techno.hpp"

template<> class Extension<FootClass> : public Extension<TechnoClass>
{
	__EXTENSION_BODY(FootClass, Extension<TechnoClass>::Offset)
public:
	using parent_type = Extension<TechnoClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<FootClass> : public FootClass
{
	__PROXY_BODY(FootClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<FootClass>>
{
	using type = Extension<FootClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(FootClass)
