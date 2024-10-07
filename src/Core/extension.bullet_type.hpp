#pragma once

#include <BulletTypeClass.h>

#include "extension.object_type.hpp"

#include <Helpers/Macro.h>
#include <Utilities/TemplateDef.h>
#include <New/Type/LaserTrailTypeClass.h>
#include <Ext/Bullet/Trajectories/PhobosTrajectory.h>

#include <optional>

template<> class Extension<BulletTypeClass> : public Extension<ObjectTypeClass>
{
	__EXTENSION_BODY(BulletTypeClass, Extension<ObjectTypeClass>::Offset)
public:
	using parent_type = Extension<ObjectTypeClass>;
public:
	constexpr Extension(base_type& base) : parent_type(base) { }

	ArmorType* Armor;
	bool Interceptable;
	bool Interceptable_DeleteOnIntercept;
	WeaponTypeClass* Interceptable_WeaponOverride;
	ValueableIdxVector<LaserTrailTypeClass> LaserTrail_Types;
	double Gravity;

	PhobosTrajectoryType* TrajectoryType;// TODO: why not unique_ptr
	double Trajectory_Speed;

	bool Shrapnel_AffectsGround;
	bool Shrapnel_AffectsBuildings;
	std::optional<bool> SubjectToLand;
	bool SubjectToLand_Detonate;
	std::optional<bool> SubjectToWater;
	bool SubjectToWater_Detonate;

	std::optional<Leptons> ClusterScatter_Min;
	std::optional<Leptons> ClusterScatter_Max;

	bool AAOnly;
	bool Arcing_AllowElevationInaccuracy;
	WeaponTypeClass* ReturnWeapon;

	// Ares 0.7
	std::optional<Leptons> BallisticScatter_Min;
	std::optional<Leptons> BallisticScatter_Max;
};

template<> struct Proxy<BulletTypeClass> : public ObjectTypeClass
{
	__PROXY_BODY(BulletTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

template<> struct Formatter::Metadata<BulletTypeClass>
{
	using base_type = BulletTypeClass;
	using extension_type = Extension<BulletTypeClass>;

	static constexpr auto chain() noexcept
	{
		auto v = &extension_type::Armor;
		using t = decltype(((extension_type*) nullptr)->*v);

		auto const chain = Formatter::make_chain(static_cast<extension_type*>(nullptr)
			, &extension_type::Armor, "Armor"
			, &extension_type::Interceptable, "Interceptable"
			, &extension_type::Interceptable_DeleteOnIntercept, "Interceptable.DeleteOnIntercept"
			, &extension_type::Interceptable_WeaponOverride, "Interceptable.WeaponOverride"
			, &extension_type::Gravity, "Gravity"
			, &extension_type::TrajectoryType, "Trajectory"
			, &extension_type::Trajectory_Speed, "Trajectory.Speed"
			, &extension_type::Shrapnel_AffectsGround
		);
		return chain;
	}
};
