#include "Body.h"

#include <HouseClass.h>

#include <Ext/Cell/Body.hpp>
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
