#pragma once

#include <SmudgeTypeClass.h>

#include "extension.object_type.hpp"

template<> class Extension<SmudgeTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(SmudgeTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SmudgeTypeClass> : public SmudgeTypeClass
{
	__PROXY_BODY(SmudgeTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<SmudgeTypeClass>>
{
	using type = Extension<SmudgeTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(SmudgeTypeClass)
