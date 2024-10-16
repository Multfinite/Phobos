#pragma once

#include <BulletClass.h>

#include "extension.object.hpp"

template<> class Extension<BulletClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(BulletClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BulletClass> : public BulletClass
{
	__PROXY_BODY(BulletClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<BulletClass>>
{
	using type = Extension<BulletClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(BulletClass)
