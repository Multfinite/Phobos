#include "Body.h"

#include <HouseClass.h>
#include <BuildingClass.h>

#include <Ext/Cell/Body.hpp>
#include <Ext/Techno/Body.h>
#include <Ext/Building/Body.h>
#include <Common/AreaAffection.Post.hpp>

DEFINE_HOOK(0x7037DD, TechnoClass__DoCloak_Quiet, 0x10)
{
	enum
	{
		CHECK_ARG = 0x7037E7,
		PLAY_SOUND = 0x7037E9,
		SKIP_SOUND = 0x703819
	};

	GET(TechnoClass*, pThis, ESI);

	// restored code
	pThis->CloakProgress.Step = 1;

	auto pExt = TechnoExt::ExtMap.Find(pThis);
	switch (pExt->TypeExtData->Cloak_In_SoundMode)
	{
	case(CloakSoundMode::Sound):
		return PLAY_SOUND;
	case(CloakSoundMode::Silence):
		return SKIP_SOUND;
	case(CloakSoundMode::Default):
	default:
		return CHECK_ARG;
	}
}

DEFINE_HOOK(0x70372A, TechnoClass__DoUncloak_Quiet, 0x10)
{
	enum
	{
		CHECK_ARG = 0x703734,
		PLAY_SOUND = 0x703736,
		SKIP_SOUND = 0x703766
	};

	GET(TechnoClass*, pThis, ESI);

	// restored code
	pThis->CloakProgress.Step = 1;

	auto pExt = TechnoExt::ExtMap.Find(pThis);
	switch (pExt->TypeExtData->Cloak_Out_SoundMode)
	{
	case(CloakSoundMode::Sound):
		return PLAY_SOUND;
	case(CloakSoundMode::Silence):
		return SKIP_SOUND;
	case(CloakSoundMode::Default):
	default:
		return CHECK_ARG;
	}
}

DEFINE_HOOK(0x4D85FA, FootClass__Per_Cell_Process__ReplaceSensorLogic, 0x6)
{
	enum
	{
		SKIP_SENSORS = 0x4D8627,
		ORIGINAL = 0
	};

	GET(FootClass*, pThis, ESI);

	auto* pExt = TechnoExt::ExtMap.Find(pThis);
	auto* pType = pThis->GetTechnoType();
	auto* pTypeExt = pExt->TypeExtData;

	AreaAffection::PerCellProcess(pThis, pExt, pType, pTypeExt);

	// We have reimplemented vanilla behavior in `AreaAffection::PerCellProcess` --Multfinite
	return SKIP_SENSORS;
}

/*
DEFINE_HOOK(0x70DA91, TechnoClass__SensorAI__RadarEvent, 0x4B)
{

}
*/

DEFINE_HOOK(0x6F4EB0, TechnoClass__RetargetingCloak, 0x5)
{
	GET(TechnoClass*, pThis, ECX);
	auto* pExt = TechnoExt::ExtMap.Find(pThis);

	pExt->RetargetingCloak();

	return 0x6F508A; // retn
}

DEFINE_HOOK(0x70C5A0, TechnoClass__Is_Cloakable, 0x6)
{
	auto retn = [&R](bool r) -> uint32_t
	{
		R->AL(r);
		return  0x70C5AB; // retn
	};

	GET(TechnoClass*, pThis, ECX);
	auto pExt = TechnoExt::ExtMap.Find(pThis);
	return retn(pExt->IsCloakable());
}

DEFINE_HOOK(0x70D420, TechnoClass__IsSensedOnCellByPlayer, 0x5)
{
	auto retn = [&R](bool r) -> uint32_t
	{
		R->AL(r);
		return  0x70D455; // retn
	};

	GET(TechnoClass*, pThis, ECX);
	auto pExt = TechnoExt::ExtMap.Find(pThis);
	return retn(HouseClass::CurrentPlayer && pExt->IsDetectedBy(HouseClass::CurrentPlayer));
}

DEFINE_HOOK(0x70D460, TechnoClass__IsSensedOnCellBy, 0x8)
{
	auto retn = [&R](bool r) -> uint32_t
	{
		R->AL(r);
		return  0x70D490; // retn 4
	};

	GET(TechnoClass*, pThis, ECX);
	GET_STACK(HouseClass*, pSubject, STACK_OFFSET(0x0, 0x4));
	auto pExt = TechnoExt::ExtMap.Find(pThis);
	return retn(pSubject && pExt->IsDetectedBy(pSubject));
}

DEFINE_HOOK(0x6FBDC0, TechnoClass__Is_Ready_To_Cloak, 0x5)
{
	auto retn = [&R](bool r) -> uint32_t
	{
		R->EAX(r);
		return  0x6FBEAB; // retn
	};

	GET(TechnoClass*, pThis, ECX);
	auto pExt = TechnoExt::ExtMap.Find(pThis);
	return retn(pExt->IsReadyToCloak());
}

/*
DEFINE_HOOK(0x4578C0, BuildingClass__ShouldNotBeCloaked, 0x5)
{
	return 0;
}
*/

/*
DEFINE_HOOK(0x6FBC90, TechnoClass__ShouldNotBeCloaked, 0x5)
{

}
*/

/*
// It's just redefinition to avoid potential bugs.
// This did not test cloak VS sensor VS electronic warfate
// and just says if any friendly CloakType::Stealth is present.
// --Multfinite
DEFINE_HOOK(0x4870B0, CellClass__IsHouseCloakPresent, 0x7)
{
	GET(CellClass*, pThis, ECX);
	GET_STACK(char, houseId, STACK_OFFSET(0x0, 0x4));
	auto pExt = CellExt::ExtMap.Find(pThis);
	auto house = HouseClass::FindByIndex(houseId);

	auto r = pExt->AreaAffectionCache->IllusoryOf(house);

	// Problem: we can not say nothing about testing layer.

	return 0x4870C8; // retn 4
}

DEFINE_HOOK(0x486800, CellClass__DrawObjectsCloaked, 0x5)
{
	auto retn = [&R](bool r) -> uint32_t
	{
		R->AL(r);
		return  0x48682A; // retn
	};

	GET(CellClass*, pThis, ECX);
	GET_STACK(int, houseId, STACK_OFFSET(0x0, 0x4));
	auto pExt = CellExt::ExtMap.Find(pThis);
	return retn(pExt->DrawObjectsCloaked(houseId));
}
*/

DEFINE_HOOK(0x6FB740, TechnoClass__Cloaking_AI, 0x5)
{
	GET(TechnoClass*, pThis, ECX);
	GET_STACK(bool, a2, STACK_OFFSET(0x0, 0x4));

	auto pExt = TechnoExt::ExtMap.Find(pThis);
	pExt->CloakingAI(a2);

	return 0x6FB8B6; // retn
}


DEFINE_HOOK(0x454DB0, BuildingClass__Cloaking_AI, 0x5)
{
	GET(BuildingClass*, pThis, ECX);
	GET_STACK(bool, a2, STACK_OFFSET(0x0, 0x4));

	auto pExt = BuildingExt::ExtMap.Find(pThis);
	pExt->CloakingAI(a2);

	return 0x4550D6; // retn
}

