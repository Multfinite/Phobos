#include "Senses.hpp"

#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

Senses::ScanResult::ScanResult(HouseClass* pSubject, CloakTypeClass* pCloakType) :
	Subject(pSubject), CloakType(pCloakType)
{ }

template<typename T, typename ...TContainers>
inline void remove(T _Val, TContainers&... containers)
{
	([&]{
		containers.remove(_Val);
	}(), ...);
}
template<typename ...TContainers>
inline void clear(TContainers&... containers)
{
	([&]
	{
		containers.clear();
	}(), ...);
}

void Senses::SensorLayerCache::Add(SensorClass* pSensor, SensorTypeClass::LayerFlags& flags)
{
	if (std::find(Items.cbegin(), Items.cend(), pSensor) == Items.cend())
		return;

	Items.push_back(pSensor);
	if (pSensor->Type->Selectable)
		++Selectables;

	auto pairs =
	{
		  std::pair<bool, decltype(Detectors)&>(flags.Scan, Detectors)
		, std::pair<bool, decltype(Detectors)&>(flags.Track, Trackers)
		, std::pair<bool, decltype(Detectors)&>(flags.Display, Displayers)
	};
	for (auto& p : pairs)
		if (p.first)
			p.second.push_back(pSensor);
}

void Senses::SensorLayerCache::Remove(SensorClass* pSensor)
{
	if (!Items.remove(pSensor)) return;

	if(pSensor->Type->Selectable)
		--Selectables;

	remove(pSensor
		, Decloakers
		, Detectors
		, Trackers
		, Displayers
	);
}

void Senses::SensorLayerCache::Clear()
{
	Selectables = 0;

	clear(
		  Decloakers
		, Detectors
		, Trackers
		, Displayers
	);
}

void Senses::SensorLayerCache::Scan(bool isShared, bool onlyDecloakers
			, std::list<SensorClass*>& items
			, std::list<SensorClass*>& detectors, int& selectables
			, std::list<SensorClass*>& decloakers
			, std::list<SensorClass*>& trackers
			, std::list<SensorClass*>& displayers
) const {
	decloakers.insert(decloakers.end(), Decloakers.begin(), Decloakers.end());
	if (onlyDecloakers) return;

	std::list<SensorClass*> const& detectorsSrc = Detectors.select(isShared);
	std::list<SensorClass*> const& trackersSrc = Trackers.select(isShared);
	std::list<SensorClass*> const& displayersSrc = Displayers.select(isShared);

	selectables += Selectables;

	detectors.insert(detectors.end(), detectorsSrc.begin(), detectorsSrc.end());
	trackers.insert(trackers.end(), trackersSrc.begin(), trackersSrc.end());
	displayers.insert(displayers.end(), displayersSrc.begin(), displayersSrc.end());
}

void Senses::Scan::Clear()
{
	Items.clear();
	for (auto* sg : { &Air, &Ground, &Subterannean })
		sg->Clear();
}

void Senses::Scan::Register(SensorClass* pSensor)
{
	if (std::find(Items.begin(), Items.end(), pSensor) != Items.end())
		return;
	Items.push_back(pSensor);

	auto pairs = {
		  std::pair<SensorTypeClass::LayerFlags&, SensorLayerCache&>(pSensor->Type->Air, Air)
		, std::pair<SensorTypeClass::LayerFlags&, SensorLayerCache&>(pSensor->Type->Ground, Ground)
		, std::pair<SensorTypeClass::LayerFlags&, SensorLayerCache&>(pSensor->Type->Subterannean, Subterannean)
	};
	for (auto& p : pairs)
		if (p.first.HasEffect())
			p.second.Add(pSensor, p.first);
}

void Senses::Scan::Unregister(SensorClass* pSensor)
{
	if (Items.remove(pSensor))
		for (auto* sg : { &Air, &Ground, &Subterannean })
			sg->Remove(pSensor);
}
