#pragma once

#include <VoxelAnimClass.h>

#include "extension.object.hpp"

template<> class Extension<VoxelAnimClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(VoxelAnimClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<VoxelAnimClass> : public VoxelAnimClass
{
	__PROXY_BODY(VoxelAnimClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<VoxelAnimClass>>
{
	using type = Extension<VoxelAnimClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(VoxelAnimClass)
