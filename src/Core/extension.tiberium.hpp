#pragma once

#include <TiberiumClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<TiberiumClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(TiberiumClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TiberiumClass> : public TiberiumClass
{
	__PROXY_BODY(TiberiumClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<TiberiumClass>>
{
	using type = Extension<TiberiumClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(TiberiumClass)
