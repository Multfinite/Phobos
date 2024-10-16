#pragma once

#include <InfantryTypeClass.h>

#include "extension.techno_type.hpp"

template<> class Extension<InfantryTypeClass> : public Extension<TechnoTypeClass>
{
	__EXTENSION_BODY(InfantryTypeClass, Extension<TechnoTypeClass>::Offset)
public:
	using parent_type = Extension<TechnoTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<InfantryTypeClass> : public InfantryTypeClass
{
	__PROXY_BODY(InfantryTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<InfantryTypeClass>>
{
	using type = Extension<InfantryTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(InfantryTypeClass)
