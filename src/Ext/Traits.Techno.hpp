#pragma once

#include <Traits.hpp>
#include <Ext/Techno/Body.h>
#include <Ext/TechnoType/Body.h>

template<> struct extension_traits<TechnoExt>
{
	using type = TechnoTypeExt;
	using instance = TechnoExt;
};

template<> struct extension_traits<TechnoTypeExt>
{
	using type = TechnoTypeExt;
	using instance = TechnoExt;
};
