#include "SensorTypeClass.hpp"

#include <Ext/TechnoType/Body.h>
#include <Ext/BulletType/Body.h>
#include <Ext/WarheadType/Body.h>

#include <Common/AreaAffection.Post.hpp>
#include <Common/Entry.Impl.hpp>

template<> const char* Enumerable<SensorTypeClass>::GetMainSection() { return "SensorTypes"; }

void data_entry<SensorTypeClass>::Read(INI_EX& parser, const char* pSection, const char* pPrefix)
{
	Types.Read(parser, pSection, string_format("%s.Types", pPrefix).c_str());
	Radiuses.Read(parser, pSection, string_format("%s.Radiuses", pPrefix).c_str());
	Durations.Read(parser, pSection, string_format("%s.Durations", pPrefix).c_str());
	Lifetimes.Read(parser, pSection, string_format("%s.Lifetimes", pPrefix).c_str());

	IsEnabled = true;
	auto const sz = Types.size();
	for (auto const isz : { Radiuses.size(), Durations.size(), Lifetimes.size() })
		if (sz != isz)
		{
			IsEnabled = false;
			break;
		}
	if (!IsEnabled)
		Debug::Log("[Phobos] Sensor on <%s> disabled because some properties is incorrect. \n", pSection);
}

#pragma region(save/load)

template <class T>
bool data_entry<SensorTypeClass>::Serialize(T& stm)
{
	return stm
		.Process(this->OwnerType)
		.Process(this->Types)
		.Process(this->Radiuses)
		.Process(this->Durations)
		.Process(this->Lifetimes)
		.Success();
}

#pragma endregion(save/load)

void SensorTypeClass::LayerFlags::Read(INI_EX& parser, const char* pSection, const char* pPrefix)
{
	Scan.Read(parser, pSection, string_format("%s.Scan", pPrefix).c_str());
	Track.Read(parser, pSection, string_format("%s.Track", pPrefix).c_str());
	Decloak.Read(parser, pSection, string_format("%s.Decloak", pPrefix).c_str());
	Display.Read(parser, pSection, string_format("%s.Display", pPrefix).c_str());
}

#pragma region(save/load)

template <class T>
bool SensorTypeClass::LayerFlags::Serialize(T& stm)
{
	return stm
		.Process(this->Prefix)
		.Process(this->Scan)
		.Process(this->Track)
		.Process(this->Decloak)
		.Process(this->Display)
		.Success();
}

void SensorTypeClass::LoadFromINI(CCINIClass* pINI)
{
	const char* pSection = this->Name;
	if (strcmp(pSection, NONE_STR) == 0)
		return;

	INI_EX exINI(pINI);

	AllowedToScan.Read(exINI, pSection, "Senses.Allowed");
	ForbiddenToScan.Read(exINI, pSection, "Senses.Forbidden");
	Sharing.Read(exINI, pSection, "Sharing");
	IsStrong.Read(exINI, pSection, "IsStrong");
	Selectable.Read(exINI, pSection, "Selectable");
	Delay.Read(exINI, pSection, "Delay");
	Duration.Read(exINI, pSection, "Duration");
	CellIncrement.Read(exINI, pSection, "CellIncrement");

	for(auto& kvp : {
		std::make_pair(&Air, "Air")
	  , std::make_pair(&Ground, "Ground")
	  , std::make_pair(&Subterannean, "Subterannean")
	})
		kvp.first->Read(exINI, pSection, kvp.second);

	ForceShadows.Read(exINI, pSection, "ForceShadows");
	InMovement.Read(exINI, pSection, "InMovement");
	Animation.Read(exINI, pSection, "Animation");
	Warn.Read(exINI, pSection, "Warn");
	WarnEva.Read(exINI, pSection, "Warn.Eva");
}

template <typename T>
inline void SensorTypeClass::Serialize(T& Stm)
{
	Stm
		.Process(AllowedToScan)
		.Process(ForbiddenToScan)
		.Process(Sharing)
		.Process(IsStrong)
		.Process(Selectable)
		.Process(Delay)
		.Process(Duration)
		.Process(CellIncrement)
		.Process(Air).Process(Ground).Process(Subterannean)
		.Process(ForceShadows)
		.Process(InMovement)
		.Process(Animation)
		.Process(Warn)
		.Process(WarnEva)
		;
}

#pragma endregion(save/load)
