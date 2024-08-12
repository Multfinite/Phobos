#include "SensorTypeClass.hpp"

#include <Ext/TechnoType/Body.h>
#include <Ext/BulletType/Body.h>
#include <Ext/WarheadType/Body.h>

#include <Common/AreaAffection.Post.hpp>
#include <Common/Entry.Post.hpp>

void SensorTypeClass::DataEntry::LoadFromINI(CCINIClass* pINI, const char* pSection)
{
	INI_EX exINI(pINI);

	Types.Read(exINI, pSection, "Sensor.Types");
	Radiuses.Read(exINI, pSection, "Sensor.Radiuses");
	Durations.Read(exINI, pSection, "Sensor.Durations");
	Lifetimes.Read(exINI, pSection, "Sensor.Lifetimes");

	IsEnabled =
		Types.HasValue() && Radiuses.HasValue() &&
		!Types.empty() && Radiuses.empty() &&
		Types.size() == Radiuses.size();
	if (!IsEnabled && (Types.HasValue() || Radiuses.HasValue()))
		Debug::Log("[Phobos] Sensor on <%s> disabled because some properties is incorrect. \n", pSection);
}

#pragma region(save/load)

template <class T>
bool SensorTypeClass::DataEntry::Serialize(T& stm)
{
	return stm
		.Process(this->OwnerType)
		.Process(this->Types)
		.Process(this->Radiuses)
		.Process(this->Durations)
		.Process(this->Lifetimes)
		.Success();
}

bool SensorTypeClass::DataEntry::Load(PhobosStreamReader& stm, bool registerForChange)
{
	return this->Serialize(stm);
}

bool SensorTypeClass::DataEntry::Save(PhobosStreamWriter& stm) const
{
	return const_cast<SensorTypeClass::DataEntry*>(this)->Serialize(stm);
}

#pragma endregion(save/load)


void SensorTypeClass::LayerFlags::LoadFromINI(CCINIClass* pINI, const char* pSection)
{
	INI_EX exINI(pINI);

	Scan.Read(exINI, pSection, (Prefix + ".Detect").c_str());
	Track.Read(exINI, pSection, (Prefix + ".Track").c_str());
	Decloak.Read(exINI, pSection, (Prefix + ".Decloak").c_str());
	Display.Read(exINI, pSection, (Prefix + ".Display").c_str());
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

bool SensorTypeClass::LayerFlags::Load(PhobosStreamReader& stm, bool registerForChange)
{
	return this->Serialize(stm);
}

bool SensorTypeClass::LayerFlags::Save(PhobosStreamWriter& stm) const
{
	return const_cast<SensorTypeClass::LayerFlags*>(this)->Serialize(stm);
}

#pragma endregion(save/load)
