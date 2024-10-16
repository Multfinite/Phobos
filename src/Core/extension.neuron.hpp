#pragma once

#include <NeuronClass.h>

#include "extension.abstract.hpp"

template<> class Extension<NeuronClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(NeuronClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<NeuronClass> : public NeuronClass
{
	__PROXY_BODY(NeuronClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<NeuronClass>>
{
	using type = Extension<NeuronClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(NeuronClass)
