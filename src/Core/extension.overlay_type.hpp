#pragma once

#include <OverlayTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<OverlayTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(OverlayTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<OverlayTypeClass> : public OverlayTypeClass
{
	__PROXY_BODY(OverlayTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<OverlayTypeClass>>
{
	using type = Extension<OverlayTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(OverlayTypeClass)
