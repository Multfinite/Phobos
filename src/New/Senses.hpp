#pragma once

#include <map>
#include <list>

#include <HouseClass.h>

#include <New/Type/SensorTypeClass.hpp>
#include <New/Type/CloakTypeClass.hpp>
#include <New/Type/ElectronicWarfareTypeClass.hpp>

struct DetectResult
{
	struct SensorGroup
	{
		std::list<SensorClass*> Sensors;
		std::list<SensorClass*> Decloakers;

		inline bool IsDetected() const { return !Sensors.empty(); }
		inline bool IsDecloaked() const { return !Decloakers.empty(); }
	};

	// Checker's house
	HouseClass* Subject;

	// Cloak type to test
	CloakTypeClass* CloakType;

	SensorGroup Air, Ground, Subterannean;

	DetectResult(HouseClass* pSubject, CloakTypeClass* pCloakType);
};

struct Senses
{
	struct SensorGroup
	{
		std::list<SensorClass*> Sensors;
		std::list<SensorClass*> SharedSensors;
		std::list<SensorClass*> Decloakers;

		void Add(SensorClass* pSensor, SensorTypeClass::LayerFlags& flags);
		void Remove(SensorClass* pSensor);
		void Clear();

		void Detect(
			std::list<SensorClass*>& sensors,
			std::list<SensorClass*>& decloakers,
			bool isSharer) const;
	};

	std::list<SensorClass*> Sensors;
	SensorGroup Air, Ground, Subterannean;

	Senses() = default;

	void Clear();
	void Register(SensorClass* pSensor);
	void Unregister(SensorClass* pSensor);
};
