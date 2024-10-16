#pragma once

#include <ScriptTypeClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<ScriptTypeClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(ScriptTypeClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<ScriptTypeClass> : public ScriptTypeClass
{
	__PROXY_BODY(ScriptTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<ScriptTypeClass>>
{
	using type = Extension<ScriptTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(ScriptTypeClass)
