#pragma once

#include <Traits.hpp>
#include <Ext/Cell/Body.hpp>

template<> struct extension_traits<CellExt>
{
	using instance = CellExt;
};
