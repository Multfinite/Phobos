#pragma once

#include <DiskLaserClass.h>

#include "extension.abstract.hpp"

template<> class Extension<DiskLaserClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(DiskLaserClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<DiskLaserClass> : public DiskLaserClass
{
	__PROXY_BODY(DiskLaserClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<DiskLaserClass>>
{
	using type = Extension<DiskLaserClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(DiskLaserClass)
