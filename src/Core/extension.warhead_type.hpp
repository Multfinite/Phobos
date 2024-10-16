#pragma once

#include <WarheadTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<WarheadTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(WarheadTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<WarheadTypeClass> : public WarheadTypeClass
{
	__PROXY_BODY(WarheadTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<WarheadTypeClass>>
{
	using type = Extension<WarheadTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(WarheadTypeClass)
