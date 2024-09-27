#include "CloakTypeClass.hpp"

#include <Ext/TechnoType/Body.h>
#include <Ext/BulletType/Body.h>
#include <Ext/WarheadType/Body.h>

#include <Common/AreaAffection.Post.hpp>
#include <Common/Entry.Impl.hpp>

template<> const char* Enumerable<CloakTypeClass>::GetMainSection() { return "CloakTypes"; }

void CloakTypeClass::Layer::Read(INI_EX& exINI, const char* pSection, const char* pPrefix)
{
	Enabled.Read(exINI, pSection, string_format("%s.Enabled", pPrefix).c_str());
	SoundIn.Read(exINI, pSection, string_format("%s.Sound.In", pPrefix).c_str());
	SoundOut.Read(exINI, pSection, string_format("%s.Sound.Out", pPrefix).c_str());
}

template <typename T>
void CloakTypeClass::Layer::Serialize(T& Stm)
{
	Stm
		.Process(Enabled)
		.Process(SoundIn)
		.Process(SoundOut);
}

void CloakTypeClass::EnemyControl::Read(INI_EX& parser, const char* pSection, const char* pPrefix)
{
	Enabled.Read(parser, pSection, string_format("%s.Enabled", pPrefix).c_str());
	Warn.Read(parser, pSection, string_format("%s.Warn", pPrefix).c_str());
	Eva.Read(parser, pSection, string_format("%s.Forbidden", pPrefix).c_str());
	Raport.Read(parser, pSection, string_format("%s.Forbidden", pPrefix).c_str());
}

template<typename T>
void CloakTypeClass::EnemyControl::Serialize(T& Stm)
{
	Stm
		.Process(Enabled)
		.Process(Warn)
		.Process(Eva)
		.Process(Raport);
}


void CloakTypeClass::Stealth::Read(INI_EX& parser, const char* pSection)
{
	Stages.Read(parser, pSection, "Type.Stealth.Stages");
	Durations.Read(parser, pSection, "Type.Stealth.Durations");
}

template<typename T>
void CloakTypeClass::Stealth::Serialize(T& Stm)
{
	Stm
		.Process(Stages)
		.Process(Durations);
}

void CloakTypeClass::Disguise::Read(INI_EX& parser, const char* pSection)
{
	Infantry.Read(parser, pSection, "Type.Disguise.Infantry");
	Vehicles.Read(parser, pSection, "Type.Disguise.Vehicles");
	Naval.Read(parser, pSection, "Type.Disguise.Naval");
	Aircraft.Read(parser, pSection, "Type.Disguise.Aircraft");
	Target.Read(parser, pSection, "Type.Disguise.Target");
	EnemyControl.Read(parser, pSection, "Type.Disguise.EnemyControl");
}

template<typename T>
void CloakTypeClass::Disguise::Serialize(T& Stm)
{
	Stm
		.Process(Infantry)
		.Process(Vehicles)
		.Process(Naval)
		.Process(Aircraft)
		.Process(Target)
		.Process(EnemyControl);
}

void CloakTypeClass::Camouflage::Read(INI_EX& parser, const char* pSection)
{
	Overlays.Read(parser, pSection, "Type.Camouflage.Overlays");
	Sound.Read(parser, pSection, "Type.Camouflage.Sound");
}

template<typename T>
void CloakTypeClass::Camouflage::Serialize(T& Stm)
{
	Stm
		.Process(Overlays)
		.Process(Sound);
}

void data_entry<CloakTypeClass>::Read(INI_EX& parser, const char* pSection, const char* pPrefix)
{
	Types.Read(parser, pSection, string_format("%s.Types").c_str());
	Self.Read(parser, pSection, string_format("%sSelf").c_str());
	Radiuses.Read(parser, pSection, string_format("%sRadiuses").c_str());
	Targets.Read(parser, pSection, string_format("%sTargets").c_str());

	Warn.Read(parser, pSection, string_format("%sWarn").c_str());

	IsEnabled = true;
	auto const sz = Types.size();
	for(auto const isz : { Radiuses.size(), Self.size(), Targets.size() })
		if (sz != isz)
		{
			IsEnabled = false;
			break;
		}

	if (!IsEnabled)
		Debug::Log("[Phobos] Cloak on <%s> disabled because some properties is incorrect. \n", pSection);
}

void CloakTypeClass::LoadFromINI(CCINIClass* pINI)
{
	const char* pSection = this->Name;
	if (strcmp(pSection, NONE_STR) == 0)
		return;

	INI_EX exINI(pINI);

	Delay.Read(exINI, pSection, "Delay");
	InMovement.Read(exINI, pSection, "InMovement");
	Shadow.Read(exINI, pSection, "Shadow");
	Sharing.Read(exINI, pSection, "Sharing");

	Type.Read(exINI, pSection, "Type");
	switch (Type.Get())
	{
		case(CloakType::Stealth):
			Stealth.Read(exINI, pSection); break;
		case(CloakType::Disguise):
			Disguise.Read(exINI, pSection); break;
		case(CloakType::Camouflage):
			Camouflage.Read(exINI, pSection); break;
	}

	for (auto& kvp : {
		std::make_pair(&Air, "Air")
	  , std::make_pair(&Ground, "Ground")
	  , std::make_pair(&Subterannean, "Subterannean") })
		kvp.first->Read(exINI, pSection, kvp.second);

	Warn.Read(exINI, pSection, "Warn");
	WarnEva.Read(exINI, pSection, "Warn.Eva");
}

template <typename T>
void CloakTypeClass::Serialize(T& Stm)
{
	Stm
		.Process(Delay)
		.Process(InMovement)
		.Process(Shadow)
		.Process(Sharing)
		.Process(Type)
		.Process(Warn)
		.Process(WarnEva)
		;

	for (auto* l : { &Air, &Ground, &Subterannean })
		Stm.Process(*l);

	switch (Type.Get())
	{
		case(CloakType::Stealth):
			Stealth.Serialize(Stm) break;
		case(CloakType::Disguise):
			Disguise.Serialize(Stm); break;
		case(CloakType::Camouflage):
			Camouflage.Serialize(Stm); break;
	}
}

#pragma region(save/load)

template <class T>
bool data_entry<CloakTypeClass>::Serialize(T& stm)
{
	return stm
		.Process(this->OwnerType)
		.Process(this->Types)
		.Process(this->Radiuses)
		.Process(this->Warn)
		.Success();
}

bool data_entry<CloakTypeClass>::Load(PhobosStreamReader& stm, bool registerForChange)
{
	return this->Serialize(stm);
}

bool data_entry<CloakTypeClass>::Save(PhobosStreamWriter& stm) const
{
	return const_cast<data_entry<CloakTypeClass>*>(this)->Serialize(stm);
}

#pragma endregion(save/load)
