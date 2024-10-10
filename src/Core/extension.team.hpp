#pragma once

#include <TeamClass.h>

#include "extension.abstract.hpp"

#include <vector>

template<> class Extension<TeamClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TeamClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
public:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TeamClass> : public TeamClass
{
	__PROXY_BODY(TeamClass)
	__PROXY_MEMORY_MANAGEMENT
};

