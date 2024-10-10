#pragma once

#include "core.hpp"

enum struct ExtensionIdentifier : DWORD
{
	/* Speculations or new (reserved) */

	AbstractClass = 0x0
	, AbstractTypeClass = 0xFFFFFF00
	, AITriggerTypeClass = 0xFFFFFF01
	, AircraftClass = 0xFFFFFF02
	, AircraftTypeClass = 0xFFFFFF03
	, AlphaShapeClass = 0xFFFFFF04
	, AirstrikeClass = 0xFFFFFF05
	, BombClass = 0xFFFFFF06
	, BuildingLightClass = 0xFFFFFF07
	, CaptureManagerClass = 0xFFFFFF08
	, DiskLaserClass = 0xFFFFFF09
	, EMPulseClass = 0xFFFFFF10
	, FactoryClass = 0xFFFFFF11
	, HouseClass = 0xFFFFFF12
	, InfantryClass = 0xFFFFFF13
	, InfantryTypeClass = 0xFFFFFF14
	, IsometricTileTypeClass = 0xFFFFFF15
	, LightSourceClass = 0xFFFFFF16
	, MissionClass = 0xFFFFFF17
	, NeuronClass = 0xFFFFFF18
	, ObjectClass = 0xFFFFFF19
	, ObjectTypeClass = 0xFFFFFF20
	, OverlayClass = 0xFFFFFF21
	, ParasiteClass = 0xFFFFFF23
	, ParticleClass = 0xFFFFFF24
	, ParticleTypeClass = 0xFFFFFF25
	, RadioClass = 0xFFFFFF27
	, ScriptTypeClass = 0xFFFFFF29
	, SlaveManagerClass = 0xFFFFFF31
	, SmudgeClass = 0xFFFFFF32
	, SmudgeTypeClass = 0xFFFFFF33
	, SpawnManageClass = 0xFFFFFF34
	, SuperClass = 0xFFFFFF35
	, TacticalClass = 0xFFFFFF38
	, TagTypeClass = 0xFFFFFF39
	, TaskForceClass = 0xFFFFFF40
	, TeamTypeClass = 0xFFFFFF41
	, TeamClass = 0xFFFFFF42
	, TemporalClass = 0xFFFFFF43
	, TerrainClass = 0xFFFFFF44
	, TriggerClass = 0xFFFFFF45
	, UnitClass = 0xFFFFFF46
	, UnitTypeClass = 0xFFFFFF47
	, VeinholeMonsterClass = 0xFFFFFF48
	, WaveClass = 0xFFFFFF49
	, WaypointTypeClass = 0xFFFFFF50

	/* Old definitions */

	, AnimClass = 0xAAAAAAAA
	, AnimTypeClass = 0xEEEEEEEE
	, BuildingClass = 0x87654321
	, BuildingTypeClass = 0x11111111
	, BulletClass = 0x2A2A2A2A
	, BulletTypeClass = 0xF00DF00D
	, HouseTypeClass = 0x19191919 // 0x11111111
	, OverlayTypeClass = 0xADF48498
	, ParticleSystemClass = 0xF9984EFE
	, ParticleSystemTypeClass = 0xEAFEEAFE 
	, RadSiteClass = 0x88446622
	, RulesClass = 0x12341234
	, ScenarioClass = 0xABCD1695
	, ScriptClass = 0x3B3B3B3B
	, SideClass = 0x05B10501
	, SidebarClass = 0x51DEBA12
	, SWTypeClass = 0x18181818 // 0x11111111
	, TActionClass = 0x91919191
	, TeamClass = 0x414B4B41
	, TechnoClass = 0x55555555
	, TechnoTypeClass = 0x17171717 // 0x11111111
	, TerrainTypeClass = 0xBEE78007
	, TEventClass = 0x92929292
	, TiberiumClass = 0xAABBCCDD
	, VoxelAnimClass = 0xAAAAAACC
	, VoxelAnimTypeClass = 0xAAAEEEEE
	, WarheadTypeClass = 0x22222222
	, WeaponTypeClass = 0x33333333 // 0x22222222
	, CellClass = 0x91828291
};

#define __EXTENSION_BODY_PERMANENT(BaseClass) \
	friend std::ostream& operator<< (std::ostream& s, Extension<BaseClass> const& o); \
	friend std::istream& operator>>(std::istream& s, Extension<BaseClass>& o); \
\

/*!
* @brief Generic implementation of common functionality and metadata for Extension<T = BaseClass>
*/
#define __EXTENSION_BODY(BaseClass, PointerOffset) \
	__EXTENSION_BODY_PERMANENT(BaseClass) \
public: \
	using base_type = BaseClass; \
	static constexpr DWORD Identifier = static_cast<DWORD>(ExtensionIdentifier::BaseClass); \
	static constexpr size_t Offset = PointerOffset; \
\
	constexpr operator base_type& () const noexcept { return *reinterpret_cast<base_type*>(Base); } \
	constexpr operator base_type* () const noexcept { return reinterpret_cast<base_type*>(Base); } \
	constexpr base_type& base() const noexcept { return *this; } \
private: \

/*!
* @brief Generic implementation of common functionality and metadata for Extension<T = BaseClass>
*/
#define __EXTENSION_BODY_MAPPED(BaseClass) \
	__EXTENSION_BODY_PERMANENT(BaseClass) \
public: \
	using base_type = BaseClass; \
	static constexpr DWORD Identifier = static_cast<DWORD>(ExtensionIdentifier::BaseClass); \
\
	constexpr operator base_type& () const noexcept { return *reinterpret_cast<base_type*>(Base); } \
	constexpr operator base_type* () const noexcept { return reinterpret_cast<base_type*>(Base); } \
	constexpr base_type& base() const noexcept { return *this; } \
private: \

/*!
* @brief Generic implementation of common functionality and metadata for Proxy<T = BaseClass>
*/
#define __PROXY_BODY(BaseClass) \
public: \
	using base_type = BaseClass; \
	using extension_type = Extension<base_type>; \
	\
	constexpr extension_type** ptr() const noexcept { return reinterpret_cast<extension_type**>(const_cast<std::byte*>(reinterpret_cast<std::byte const*>(this)) + extension_type::Offset); } \
	constexpr extension_type& extension() const noexcept { return **ptr(); } \
	constexpr operator extension_type& () const noexcept { return extension(); } \
	constexpr operator extension_type* () const noexcept { return &extension(); } \
private: \

/*!
* @brief Generic implementation of memory management for Proxy<T = BaseClass>
*/
#define __PROXY_MEMORY_MANAGEMENT \
public:\
	constexpr void init() noexcept \
	{ \
		*const_cast<extension_type**>(ptr())  = new extension_type(*this); \
	} \
	constexpr void deinit() noexcept \
	{ \
		delete& extension(); \
	} \
private: \
