#pragma once

#include <Traits.hpp>
#include <Ext/Bullet/Body.h>
#include <Ext/BulletType/Body.h>

template<> struct extension_traits<BulletExt>
{
	using type = BulletTypeExt;
	using instance = BulletExt;
};

template<> struct extension_traits<BulletTypeExt>
{
	using type = BulletTypeExt;
	using instance = BulletExt;
};
