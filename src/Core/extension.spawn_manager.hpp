#pragma once

#include <SpawnManagerClass.h>

#include "extension.abstract.hpp"

template<> class Extension<SpawnManagerClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(SpawnManagerClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SpawnManagerClass> : public SpawnManagerClass
{
	__PROXY_BODY(SpawnManagerClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<SpawnManagerClass>>
{
	using type = Extension<SpawnManagerClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(SpawnManagerClass)
