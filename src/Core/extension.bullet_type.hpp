#pragma once

#include <BulletTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<BulletTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(BulletTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<BulletTypeClass> : public BulletTypeClass
{
	__PROXY_BODY(BulletTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<BulletTypeClass>>
{
	using type = Extension<BulletTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(BulletTypeClass)
