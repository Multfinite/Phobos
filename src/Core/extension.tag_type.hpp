#pragma once

#include <TagTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<TagTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(TagTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TagTypeClass> : public TagTypeClass
{
	__PROXY_BODY(TagTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TagTypeClass>>
{
	using type = Extension<TagTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TagTypeClass)
