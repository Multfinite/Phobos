#pragma once

#include <AbstractClass.h>

#include "core.extensions.hpp"
#include "core.formatting.hpp"
#include "core.formatting.impl.hpp"

template<> class Extension<AbstractClass> : public IExtension
{
	__EXTENSION_BODY(AbstractClass, 0x18)
public:
	using parent_type = IExtension;
protected:
	constexpr Extension(base_type& base) : IExtension(&base) { }
};

template<> struct Proxy<AbstractClass> : public AbstractClass
{
	__PROXY_BODY(AbstractClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<AbstractClass>>
{
	using type = Extension<AbstractClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(AbstractClass)
