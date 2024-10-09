#include "extension.aircraft.hpp"

#include <BuildingClass.h>

#include <Ext/BuildingType/Body.h>
#include <Ext/Techno/Body.h>
#include <Ext/WeaponType/Body.h>

// TODO: Implement proper extended AircraftClass.

void Proxy<AircraftClass>::FireWeapon(AbstractClass* pTarget, int shotNumber = 0)
{
	if (!pTarget)
		return;

	auto weaponIndex = extension().CurrentAircraftWeaponIndex;

	if (weaponIndex < 0)
		weaponIndex = SelectWeapon(pTarget);

	auto const pWeapon = GetWeapon(weaponIndex)->WeaponType;
	auto const pWeaponExt = WeaponTypeExt::ExtMap.Find(pWeapon);

	if (pWeapon->Burst > 0)
	{
		for (int i = 0; i < pWeapon->Burst; i++)
		{
			if (pWeapon->Burst < 2 && pWeaponExt->Strafing_SimulateBurst)
				CurrentBurstIndex = shotNumber;

			Fire(pTarget, weaponIndex);
		}
	}

	if (Is_Strafe())
		extension().Strafe_BombsDroppedThisRound++;
}

// Spy plane, airstrike etc.
bool Proxy<AircraftClass>::PlaceReinforcementAircraft( CellStruct edgeCell)
{
	auto const pTypeExt = TechnoTypeExt::ExtMap.Find(GetTechnoType());
	auto coords = CellClass::Cell2Coord(edgeCell);
	coords.Z = 0;
	AbstractClass* pTarget = nullptr;

	if (pTypeExt->SpawnDistanceFromTarget.isset())
	{
		pTarget = Target ? Target : Destination;

		if (pTarget)
			coords = GeneralUtils::CalculateCoordsFromDistance(CellClass::Cell2Coord(edgeCell), pTarget->GetCoords(), pTypeExt->SpawnDistanceFromTarget.Get());
	}

	++Unsorted::IKnowWhatImDoing;
	bool result = Unlimbo(coords, DirType::North);
	--Unsorted::IKnowWhatImDoing;

	SetHeight(pTypeExt->SpawnHeight.Get(Type->GetFlightLevel()));

	if (pTarget)
		PrimaryFacing.SetDesired(GetTargetDirection(pTarget));

	return result;
}

DirType Proxy<AircraftClass>::GetLandingDir(BuildingClass* pDock)
{
	auto const poseDir = static_cast<DirType>(RulesClass::Instance->PoseDir);

	// If this is a spawnee, use the spawner's facing.
	if (auto pOwner = SpawnOwner)
		return pOwner->PrimaryFacing.Current().GetDir();

	if (pDock || HasAnyLink())
	{
		auto pLink = GetNthLink(0);

		if (auto pBuilding = pDock ? pDock : abstract_cast<BuildingClass*>(pLink))
		{
			auto const pBuildingTypeExt = BuildingTypeExt::ExtMap.Find(pBuilding->Type);
			int docks = pBuilding->Type->NumberOfDocks;
			int linkIndex = pBuilding->FindLinkIndex(this);

			if (docks > 0 && linkIndex >= 0 && linkIndex < docks)
			{
				if (!pBuildingTypeExt->AircraftDockingDirs[linkIndex].empty())
					return pBuildingTypeExt->AircraftDockingDirs[linkIndex].get();
			}
			else if (docks > 0 && !pBuildingTypeExt->AircraftDockingDirs[0].empty())
				return pBuildingTypeExt->AircraftDockingDirs[0].get();
		}
		else if (!Type->AirportBound)
			return pLink->PrimaryFacing.Current().GetDir();
	}

	int landingDir = TechnoTypeExt::ExtMap.Find(this->Type)->LandingDir.Get((int)poseDir);

	if (!Type->AirportBound && landingDir < 0)
		return PrimaryFacing.Current().GetDir();

	return static_cast<DirType>(Math::clamp(landingDir, 0, 255));
}

