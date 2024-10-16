#pragma once

#include <TerrainTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<TerrainTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(TerrainTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TerrainTypeClass> : public TerrainTypeClass
{
	__PROXY_BODY(TerrainTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TerrainTypeClass>>
{
	using type = Extension<TerrainTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TerrainTypeClass)
