#pragma once

#include <ObjectClass.h>

#include "extension.abstract.hpp"

template<> class Extension<ObjectClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(ObjectClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ObjectClass> : public ObjectClass
{
	__PROXY_BODY(ObjectClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<ObjectClass>>
{
	using type = Extension<ObjectClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ObjectClass)
