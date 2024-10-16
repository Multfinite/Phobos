#pragma once

#include <CaptureManagerClass.h>

#include "extension.abstract.hpp"

template<> class Extension<CaptureManagerClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(CaptureManagerClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<CaptureManagerClass> : public CaptureManagerClass
{
	__PROXY_BODY(CaptureManagerClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<CaptureManagerClass>>
{
	using type = Extension<CaptureManagerClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(CaptureManagerClass)
