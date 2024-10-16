#pragma once

#include <IsometricTileTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<IsometricTileTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(IsometricTileTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<IsometricTileTypeClass> : public IsometricTileTypeClass
{
	__PROXY_BODY(IsometricTileTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<IsometricTileTypeClass>>
{
	using type = Extension<IsometricTileTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(IsometricTileTypeClass)
