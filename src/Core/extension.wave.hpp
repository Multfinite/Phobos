#pragma once

#include <WaveClass.h>

#include "extension.object.hpp"

template<> class Extension<WaveClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(WaveClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<WaveClass> : public WaveClass
{
	__PROXY_BODY(WaveClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<WaveClass>>
{
	using type = Extension<WaveClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(WaveClass)
