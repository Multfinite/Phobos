#pragma once

#include <TeamClass.h>

#include "extension.abstract.hpp"

#include <vector>

template<> class Extension<TeamClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TeamClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
public:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TeamClass> : public TeamClass
{
	__PROXY_BODY(TeamClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TeamClass>>
{
	using type = Extension<TeamClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr)
		);
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TeamClass)
