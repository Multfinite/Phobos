#pragma once

#include <TriggerClass.h>

#include "extension.abstract.hpp"

template<> class Extension<TriggerClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TriggerClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TriggerClass> : public TriggerClass
{
	__PROXY_BODY(TriggerClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TriggerClass>>
{
	using type = Extension<TriggerClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TriggerClass)
