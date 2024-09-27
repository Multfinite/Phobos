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

template<> struct Proxy<RadioClass> : public MissionClass
{
	__PROXY_BODY(RadioClass)
	__PROXY_MEMORY_MANAGEMENT
};

