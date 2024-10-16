#pragma once

#include <TeamTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<TeamTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(TeamTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TeamTypeClass> : public TeamTypeClass
{
	__PROXY_BODY(TeamTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TeamTypeClass>>
{
	using type = Extension<TeamTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TeamTypeClass)
