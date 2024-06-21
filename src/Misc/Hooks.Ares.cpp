#include "../Defs.h"

#include <Memory.h>
#include "../Ext/Techno/Body.h"
#include "../Ext/TechnoType/Body.h"

#include <HouseClass.h>
#include <UnitClass.h>
#include <TechnoClass.h>
#include <FootClass.h>
#include <BuildingClass.h>
#include <InfantryClass.h>
#include <AircraftClass.h>
#include <JumpjetLocomotionClass.h>
#include <LineTrail.h>
#include <SpawnManagerClass.h>

#include <Utilities/Debug.h>
#include <Utilities/AresHelper.h>
#include <Utilities/Macro.h>

// In vanilla YR, game destroys building animations directly by calling constructor.
// Ares changed this to call UnInit() which has a consequence of doing pointer invalidation on the AnimClass pointer.
// This notably causes an issue with Grinder that restores ActiveAnim if the building is sold/destroyed while SpecialAnim is playing even if the building is gone or in limbo.
// Now it does not do this if the building is in limbo, which covers all cases from being destroyed, sold, to erased by Temporal weapons.
// There is another potential case for this with ProductionAnim & IdleAnim which is also patched here just in case.
DEFINE_HOOK_AGAIN(0x44E997, BuildingClass_Detach_RestoreAnims, 0x6)
DEFINE_HOOK(0x44E9FA, BuildingClass_Detach_RestoreAnims, 0x6)
{
	enum { SkipAnimOne = 0x44E9A4, SkipAnimTwo = 0x44EA07 };

	GET(BuildingClass*, pThis, ESI);

	if (pThis->InLimbo)
		return R->Origin() == 0x44E997 ? SkipAnimOne : SkipAnimTwo;

	return 0;
}

//0x0004432A - 0x0004372A
DEFINE_ARES3p1_HOOK(0x0004432A, _Ares_ConvertTypeTo_4432A, 8)
{
	GET(FootClass*, pSubject, EDI);
	GET_STACK(TechnoTypeClass*, pNewType, STACK_OFFSET(0x30, 0x8));
	TechnoTypeClass* pSubjectType = (TechnoTypeClass*) pSubject->GetType();

	auto currentIsJumpjet = pSubjectType->Locomotor == JumpjetLocomotionClass::ClassGUID;
	auto newIsJumpjet = pNewType->Locomotor == JumpjetLocomotionClass::ClassGUID;

	if (currentIsJumpjet && newIsJumpjet)
		return AresHelper::DynamicOffset(0x00044351);

	// Original
	R->Stack<int>(STACK_OFFSET(0x30, -0xC), 12);
	return 0;
}
