#pragma once

#include <TechnoClass.h>

#include "extension.radio.hpp"

#include <InfantryClass.h>
#include <AnimClass.h>

#include <Helpers/Macro.h>
#include <Utilities/Container.h>
#include <Utilities/TemplateDef.h>
#include <Utilities/Macro.h>
#include <New/Entity/ShieldClass.h>
#include <New/Entity/LaserTrailClass.h>

class BulletClass;

template<> class Extension<TechnoClass> : public Extension<RadioClass>
{
	__EXTENSION_BODY(TechnoClass, Extension<RadioClass>::Offset)
public:
	using parent_type = Extension<RadioClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base)
		, TypeExtData { nullptr }
		, Shield {}
		, LaserTrails {}
		, ReceiveDamage { false }
		, LastKillWasTeamTarget { false }
		, PassengerDeletionTimer {}
		, CurrentShieldType { nullptr }
		, LastWarpDistance {}
		, AutoDeathTimer {}
		, MindControlRingAnimType { nullptr }
		, DamageNumberOffset { INT32_MIN }
		, OriginalPassengerOwner {}
		, IsInTunnel { false }
		, HasBeenPlacedOnMap { false }
		, DeployFireTimer {}
		, ForceFullRearmDelay { false }
		, WHAnimRemainingCreationInterval { 0 }
	{ }
public:
	Extension<TechnoTypeClass>* TypeExtData;
	std::unique_ptr<ShieldClass> Shield;
	std::vector<LaserTrailClass> LaserTrails;
	bool ReceiveDamage;
	bool LastKillWasTeamTarget;
	CDTimerClass PassengerDeletionTimer;
	ShieldTypeClass* CurrentShieldType;
	int LastWarpDistance;
	CDTimerClass AutoDeathTimer;
	AnimTypeClass* MindControlRingAnimType;
	int DamageNumberOffset;
	bool IsInTunnel;
	bool HasBeenPlacedOnMap; // Set to true on first Unlimbo() call.
	CDTimerClass DeployFireTimer;
	bool ForceFullRearmDelay;
	int WHAnimRemainingCreationInterval;

	// Used for Passengers.SyncOwner.RevertOnExit instead of TechnoClass::InitialOwner / OriginallyOwnedByHouse,
	// as neither is guaranteed to point to the house the TechnoClass had prior to entering transport and cannot be safely overridden.
	HouseClass* OriginalPassengerOwner;
};

template<> struct Proxy<TechnoClass> : public RadioClass
{
	__PROXY_BODY(TechnoClass)
	__PROXY_MEMORY_MANAGEMENT
};

