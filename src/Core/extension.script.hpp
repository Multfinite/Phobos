#pragma once

#include <ScriptClass.h>

#include "extension.abstract.hpp"

template<> class Extension<ScriptClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(ScriptClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ScriptClass> : public ScriptClass
{
	__PROXY_BODY(ScriptClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<ScriptClass>>
{
	using type = Extension<ScriptClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ScriptClass)
