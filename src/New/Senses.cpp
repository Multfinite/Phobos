#include "Senses.hpp"

#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

DetectResult::DetectResult(HouseClass* pSubject, CloakTypeClass* pCloakType) :
	Subject(pSubject), CloakType(pCloakType)
{ }

void Senses::SensorGroup::Add(SensorClass* pSensor, SensorTypeClass::LayerFlags& flags)
{
	Sensors.push_back(pSensor);
	if (pSensor->Type->IsShared())
		SharedSensors.push_back(pSensor);
	if (flags.Decloak)
		Decloakers.push_back(pSensor);
}

void Senses::SensorGroup::Remove(SensorClass* pSensor)
{
	Sensors.remove(pSensor);
	SharedSensors.remove(pSensor);
	Decloakers.remove(pSensor);
}

void Senses::SensorGroup::Clear()
{
	Sensors.clear();
	SharedSensors.clear();
	Decloakers.clear();
}

void Senses::SensorGroup::Detect(
	std::list<SensorClass*>& sensors,
	std::list<SensorClass*>& decloakers,
	bool isSharer) const
{
	std::list<SensorClass*> const& srcSensors = isSharer ? SharedSensors : Sensors;
	sensors.insert(sensors.end(), srcSensors.begin(), srcSensors.end());
	decloakers.insert(decloakers.end(), Decloakers.begin(), Decloakers.end());
}

void Senses::Clear()
{
	Sensors.clear();
	Air.Clear();
	Ground.Clear();
	Subterannean.Clear();
}

void Senses::Register(SensorClass* pSensor)
{
	if (std::find(Sensors.begin(), Sensors.end(), pSensor) != Sensors.end())
		return;
	Sensors.push_back(pSensor);
	if (pSensor->Type->Air.Detect)
		Air.Add(pSensor, pSensor->Type->Air);
	if (pSensor->Type->Ground.Detect)
		Ground.Add(pSensor, pSensor->Type->Ground);
	if (pSensor->Type->Subterannean.Detect)
		Subterannean.Add(pSensor, pSensor->Type->Subterannean);
}

void Senses::Unregister(SensorClass* pSensor)
{
	Sensors.remove(pSensor);
	Air.Remove(pSensor);
	Ground.Remove(pSensor);
	Subterannean.Remove(pSensor);
}
