#pragma once

#include <TechnoClass.h>

#include "extension.radio.hpp"

template<> class Extension<TechnoClass> : public Extension<RadioClass>
{
	__EXTENSION_BODY(TechnoClass, Extension<RadioClass>::Offset)
public:
	using parent_type = Extension<RadioClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TechnoClass> : public RadioClass
{
	__PROXY_BODY(TechnoClass)
	__PROXY_MEMORY_MANAGEMENT
};

