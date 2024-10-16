#pragma once

#include <RadioClass.h>

#include "extension.mission.hpp"

template<> class Extension<RadioClass> : public Extension<MissionClass>
{
	__EXTENSION_BODY(RadioClass, Extension<MissionClass>::Offset)
public:
	using parent_type = Extension<MissionClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<RadioClass> : public RadioClass
{
	__PROXY_BODY(RadioClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter<Extension<RadioClass>>
{
	using type = Extension<RadioClass>;

	static constexpr auto chain() noexcept
	{
		auto const chain = make_chain(static_cast<type*>(nullptr));
		return chain;
	}

	__FORMATTER_BODY_GENERIC(type)
};

__EXTENSION_GENERIC_FORMATTING(RadioClass)
