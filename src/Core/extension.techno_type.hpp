#pragma once

#include <TechnoTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<TechnoTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(TechnoTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TechnoTypeClass> : public TechnoTypeClass
{
	__PROXY_BODY(TechnoTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TechnoTypeClass>>
{
	using type = Extension<TechnoTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TechnoTypeClass)
