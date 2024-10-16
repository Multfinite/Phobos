#pragma once

#include <SlaveManagerClass.h>

#include "extension.abstract.hpp"

template<> class Extension<SlaveManagerClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(SlaveManagerClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<SlaveManagerClass> : public SlaveManagerClass
{
	__PROXY_BODY(SlaveManagerClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<SlaveManagerClass>>
{
	using type = Extension<SlaveManagerClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(SlaveManagerClass)
