#include <InfantryClass.h>
#include <InfantryTypeClass.h>
#include <Ext/TechnoType/Body.h>

#include <Helpers/Macro.h>

#include <set>

std::set<Sequence> Standing {
	Sequence::Ready,
	Sequence::Idle1,
	Sequence::Idle2,

	Sequence::Up,

	Sequence::FireUp,
	Sequence::SecondaryFire,

	Sequence::Guard,
	Sequence::Walk,
	Sequence::Tread,
};
std::set<Sequence> Walking {
	Sequence::Guard,
	Sequence::Walk,
	Sequence::Tread,

	Sequence::Crawl,
};
std::set<Sequence> Proned {
	Sequence::Prone,

	Sequence::Down,

	Sequence::FireProne,
	Sequence::SecondaryProne,

	Sequence::Crawl,
};

inline bool contains(std::set<Sequence>& set, Sequence item)
{
	return std::find(Standing.cbegin(), Standing.cend(), item) != Standing.cend();
}

DEFINE_HOOK(0x51D9D2, InfantryClass_DoType_51D9D2, 0x6)
{
	GET(InfantryClass*, pThis, ESI);
	GET(Sequence, newState, EDI);

	auto pExtType = TechnoTypeExt::ExtMap.Find(pThis->GetTechnoType());	

	auto state = pThis->SequenceAnim;
	auto isStanding = contains(Standing, state);
	//auto isWalking = contains(Walking, state);
	auto isProned = contains(Proned, state);

	switch (newState)
	{
	case(Sequence::Ready):
	case(Sequence::Idle1):
	case(Sequence::Idle2):
		newState = pExtType->Prone_Always ? Sequence::Down : newState;
		break;
	case(Sequence::Up):
		newState = (pExtType->Prone_Always) ? Sequence::Prone : newState;
		break;
	case(Sequence::Crawl):
		if (pExtType->Prone_Sprint)
			newState = isStanding ? Sequence::Walk : Sequence::Up;
		else
			newState = isStanding ? Sequence::Down : newState;
		break;
	case(Sequence::Guard):
	case(Sequence::Walk):
	case(Sequence::Tread):
		if (pExtType->Prone_Always && !pExtType->Prone_Sprint)
			newState = isStanding ? Sequence::Down : Sequence::Crawl;
		break;
	case(Sequence::FireUp):
		if (pExtType->Prone_Always && !pExtType->Prone_PrimaryInStand)
			newState = isStanding ? Sequence::Down : Sequence::FireProne;
		break;
	case(Sequence::FireProne):
		if (pExtType->Prone_PrimaryInStand)
			newState = isStanding ? Sequence::FireUp : Sequence::Up;
		break;
	case(Sequence::SecondaryFire):
		if (pExtType->Prone_Always && !pExtType->Prone_SecondaryInStand)
			newState = isStanding ? Sequence::Down : Sequence::SecondaryProne;
		break;	
	case(Sequence::SecondaryProne):
		if (pExtType->Prone_SecondaryInStand)
			newState = isStanding ? Sequence::SecondaryFire : Sequence::Up;
		break;
#ifdef DEBUG
	case(Sequence::Prone):
	case(Sequence::Down):
		newState = newState;
		break;
	default:
		newState = newState;
		break;
#endif // DEBUG
	}

	R->EDI(newState);
	return 0;
}
