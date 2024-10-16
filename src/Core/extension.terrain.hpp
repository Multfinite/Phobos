#pragma once

#include <TerrainClass.h>

#include "extension.object.hpp"

template<> class Extension<TerrainClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(TerrainClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TerrainClass> : public TerrainClass
{
	__PROXY_BODY(TerrainClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TerrainClass>>
{
	using type = Extension<TerrainClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TerrainClass)
