#pragma once

#include <map>
#include <list>

#include <HouseClass.h>

#include <New/Type/SensorTypeClass.hpp>
#include <New/Type/CloakTypeClass.hpp>
#include <New/Type/ElectronicWarfareTypeClass.hpp>

#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

namespace Senses
{
	template<typename T>
	struct SharedGroup
	{
		std::list<T*> All;
		std::list<T*> Shared;

		inline std::list<T*> const& select(bool isShared) const { return isShared ? Shared : All; }
		inline void push_back(T* _Val)
		{
			All.push_back(_Val);
			if (_Val->Type->IsShared())
				Shared.push_back(_Val);
		}
		inline bool remove(T* _Val)
		{
			if(All.remove(_Val))
			{
				if (_Val->Type->IsShared())
					Shared.remove(_Val);
				return true;
			}
			return false;
		}
		inline void clear()
		{
			All.clear();
			Shared.clear();
		}
	};

	struct SensorLayerCache
	{
		/*!
		 * @brief provides unique items from all other groups.
		 */
		std::list<SensorClass*> Items;

		std::list<SensorClass*> Decloakers;

		SharedGroup<SensorClass> Detectors;
		SharedGroup<SensorClass> Trackers;
		SharedGroup<SensorClass> Displayers;

		int Selectables = 0;

		void Add(SensorClass* pSensor, SensorTypeClass::LayerFlags& flags);
		void Remove(SensorClass* pSensor);
		void Clear();

		void Scan(bool isShared, bool onlyDecloakers
			, std::list<SensorClass*>& items
			, std::list<SensorClass*>& detectors, int& selectables
			, std::list<SensorClass*>& decloakers
			, std::list<SensorClass*>& trackers
			, std::list<SensorClass*>& displayers
		) const;
	};

	struct Scan
	{
		std::list<SensorClass*> Items;
		SensorLayerCache Air, Ground, Subterannean;

		Scan() = default;

		void Clear();
		void Register(SensorClass* pSensor);
		void Unregister(SensorClass* pSensor);
	};

	struct ScanLayerCache
	{
		/*!
		* @brief provides unique items from all other groups.
		*/
		std::list<SensorClass*> Items;
		std::list<SensorClass*> Detectors;
		/*!
		* @brief number of `Sensors` which allow selection for sensed object.
		*/
		int Selectables = 0;
		std::list<SensorClass*> Decloakers;
		std::list<SensorClass*> Trackers;
		std::list<SensorClass*> Displayers;

		inline bool IsDetected() const { return !Detectors.empty(); }
		inline bool IsDecloaked() const { return !Decloakers.empty(); }
		inline bool IsTracked() const { return !Trackers.empty(); }
		inline bool IsDisplayed() const { return !Displayers.empty(); }
		inline bool IsSelectable() const { return Selectables > 0; }

		inline bool IsAffected() const
		{
			return IsDetected()
				|| IsDecloaked()
				|| IsTracked()
				|| IsDisplayed();
		}
	};

	struct ScanResult
	{
		// Checker's house
		HouseClass* Subject;

		// Cloak type to test
		class CloakTypeClass* CloakType;

		ScanLayerCache Air, Ground, Subterannean;

		inline ScanLayerCache& GroupOf(ObjectClass* obj)
		{
			switch (obj->InWhichLayer())
			{
				case Layer::Air:
				case Layer::Top:
					return Air;
				case Layer::Ground:
				case Layer::Surface:
					return Ground;
				case Layer::Underground:
					return Subterannean;
				case Layer::None:
				{
					Debug::Log("%s::%s: Layer is None -- WARNING!!!", __FILE__, __FUNCSIG__);
				} break;
			}
			throw std::exception(__FUNCSIG__); // handle this
		}

		ScanResult(HouseClass* pSubject, class CloakTypeClass* pCloakType);
	};

	struct Illusion
	{
		std::map<class CloakTypeClass*, SharedGroup<CloakClass>> GroupedByType;
	};

	struct IllusionLayerCache
	{
		SharedGroup<CloakClass> Items;
		std::map<CloakType, std::list<CloakClass*>> GroupedByType;

		inline bool IsStealthed() noexcept { return !GroupedByType[CloakType::Stealth].empty(); }
		inline bool IsDisguised() noexcept { return !GroupedByType[CloakType::Disguise].empty(); }
		inline bool IsCamouflaged() noexcept  { return !GroupedByType[CloakType::Camouflage].empty(); }
		inline bool IsVirtual() noexcept  { return !GroupedByType[CloakType::Virtual].empty(); }

		inline bool IsAffected() noexcept
		{
			return IsVirtual()
				|| IsStealthed()
				|| IsCamouflaged()
				|| IsDisguised();
		}

		inline void add(CloakClass& instance)
		{
			Items.push_back(&instance);
			GroupedByType[instance.Type->Type].push_back(&instance);
		}

		inline bool remove(CloakClass& instance)
		{
			if (Items.remove(&instance))
			{
				GroupedByType[instance.Type->Type].remove(&instance);
				return true;
			}
			return false;
		}

		inline void reset()
		{
			Items.clear();
			GroupedByType.clear();
		}
	};

	struct IllusionResult
	{
		SharedGroup<CloakClass> Items;
		IllusionLayerCache Air, Ground, Subterannean;

		// Cloak benefits owner
		HouseClass* Subject;

		inline IllusionLayerCache& GroupOf(ObjectClass* obj)
		{
			switch (obj->InWhichLayer())
			{
				case Layer::Air:
				case Layer::Top:
					return Air;
				case Layer::Ground:
				case Layer::Surface:
					return Ground;
				case Layer::Underground:
					return Subterannean;
				case Layer::None:
				{
					Debug::Log("%s::%s: Layer is None -- WARNING!!!", __FILE__, __FUNCSIG__);
				} break;
			}
			throw std::exception(__FUNCSIG__); // handle this
		}

		inline void add(CloakClass& instance)
		{
			Items.push_back(&instance);
			for (auto& kvp : {
				std::make_pair(&Air, &instance.Type->Air)
			  , std::make_pair(&Ground, &instance.Type->Ground)
			  , std::make_pair(&Subterannean, &instance.Type->Subterannean)
			})
				if(kvp.second->IsEnabled)
					kvp.first->add(instance);
		}

		inline bool remove(CloakClass& instance)
		{
			if (Items.remove(&instance))
			{
				for(auto* l : { &Air, &Ground, &Subterannean })
					l->remove(instance);
				return true;
			}
			return false;
		}

		inline void reset()
		{
			Items.clear();
			for (auto* l : { &Air, &Ground, &Subterannean })
				l->reset();
		}
	};
}



