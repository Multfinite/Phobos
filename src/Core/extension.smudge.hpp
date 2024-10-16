#pragma once

#include <SmudgeClass.h>

#include "extension.object.hpp"

template<> class Extension<SmudgeClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(SmudgeClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SmudgeClass> : public SmudgeClass
{
	__PROXY_BODY(SmudgeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<SmudgeClass>>
{
	using type = Extension<SmudgeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(SmudgeClass)
