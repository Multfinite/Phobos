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

