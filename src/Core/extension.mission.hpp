#pragma once

#include <MissionClass.h>

#include "extension.object.hpp"

template<> class Extension<MissionClass> : public Extension<ObjectClass>
{
	__EXTENSION_BODY(MissionClass, Extension<ObjectClass>::Offset)
public:
	using parent_type = Extension<ObjectClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<MissionClass> : public MissionClass
{
	__PROXY_BODY(MissionClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<MissionClass>>
{
	using type = Extension<MissionClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(MissionClass)
