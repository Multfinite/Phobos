#pragma once

#include <VeinholeMonsterClass.h>

#include "extension.object.hpp"

template<> class Extension<VeinholeMonsterClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(VeinholeMonsterClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<VeinholeMonsterClass> : public VeinholeMonsterClass
{
	__PROXY_BODY(VeinholeMonsterClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<VeinholeMonsterClass>>
{
	using type = Extension<VeinholeMonsterClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(VeinholeMonsterClass)
