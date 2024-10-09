#pragma once

#include <AircraftClass.h>

#include "extension.foot.hpp"

template<> class Extension<AircraftClass> : public Extension<FootClass>
{
	__EXTENSION_BODY(AircraftClass, Extension<FootClass>::Offset)
public:
	using parent_type = Extension<FootClass>;
public:
	constexpr Extension(base_type& base) : parent_type(base) { }

	int Strafe_BombsDroppedThisRound;
	int CurrentAircraftWeaponIndex;
};

template<> struct Proxy<AircraftClass> : public AircraftClass
{
	__PROXY_BODY(AircraftClass)
	__PROXY_MEMORY_MANAGEMENT

public:
	void FireWeapon(AbstractClass* pTarget, int shotNumber);
	bool PlaceReinforcementAircraft(CellStruct edgeCell);
	DirType GetLandingDir(BuildingClass* pDock = nullptr);
};

