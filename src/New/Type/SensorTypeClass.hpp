#pragma once

#include <Utilities/Enumerable.h>
#include <Utilities/Template.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>
#include <Utilities/TemplateDef.h>

#include <Ext/Rules/Body.h>
#include <TechnoClass.h>
#include <BulletClass.h>
#include <SideClass.h>
#include <HouseTypeClass.h>

#include <Utilities/Constructs.h>

#include "CloakTypeClass.hpp"

#include <Common/Entry.hpp>

class SensorTypeClass : public Enumerable<SensorTypeClass>
{
public:
	using parent_type = AbstractTypeClass;

	struct LayerFlags
	{
		/*!
		* @brief Is this detecting (not decloaking) object. It means you can see it.
		*/
		Valueable<bool> Scan;
		/*!
		* @brief Show lines like mind reader or TS sensor array
		*/
		Valueable<bool> Track;
		/*!
		* @brief Decloak sensed object?
		*/
		Valueable<bool> Decloak;
		/*!
		* @brief Is target should be displayed on radar?
		*/
		Valueable<bool> Display;
		/*!
		* @brief It will be fired at sensed object
		*/
		NullableIdx<WeaponTypeClass*> Weapon;
		/*!
		* @brief It will be shown on sensed object
		*/
		NullableIdx<AnimTypeClass*> Animation;

		LayerFlags(bool detect, bool track, bool decloak, bool display) :
			Scan(detect), Track(track), Decloak(decloak), Display(display)
		{}

		virtual void Read(INI_EX& parser, const char* pSection, const char* pPrefix);
		virtual bool Load(PhobosStreamReader& stm, bool registerForChange) { return Serialize(stm); }
		virtual bool Save(PhobosStreamWriter& stm) const { return const_cast<SensorTypeClass::LayerFlags*>(this)->Serialize(stm); }

		inline bool HasEffect() const { return Scan || Track || Decloak || Display || Weapon || Animation; }

	private:
		template <typename T>
		inline bool Serialize(T& stm);
	};

	ValueableVector<CloakTypeClass*> AllowedToScan, ForbiddenToScan;
	Valueable<EffectShareMode> Sharing { EffectShareMode::Default };
	/*!
	* @brief Controls how cloak vs sensor conflict will be solved.
	* @brief If enabled then object became sensed if any cloak types from `Senses` present.
	* @brief If disabled then object became sensed if all cloaks presented in `Senses` list.
	*/
	Valueable<bool> IsStrong { true };
	Valueable<bool> Selectable { false };

	Valueable<int> Delay { 0 }, Duration { 0 }, CellIncrement { 0 };

	LayerFlags
		Air { true, false, false, false }
	  , Ground { true, false, false, false }
	  , Subterannean { false, false, false, false };

	Valueable<bool> ForceShadows { false }, InMovement { true };
	Nullable<AnimTypeClass*> Animation;

	Valueable<bool> Warn { false };
	CollaborableIdx<VocClass*> WarnEva;
public:
	SensorTypeClass(const char* const pTitle) : Enumerable<SensorTypeClass>(pTitle) { };

	virtual ~SensorTypeClass() override = default;

	virtual void LoadFromINI(CCINIClass* pINI) override;
	virtual void LoadFromStream(PhobosStreamReader& Stm) override { Serialize(Stm); }
	virtual void SaveToStream(PhobosStreamWriter& Stm) override { Serialize(Stm); }

	inline bool IsShared() const
	{
		switch (Sharing.Get())
		{
		case EffectShareMode::Shared:
			return true;
		case EffectShareMode::Private:
			return false;
		case EffectShareMode::Default:
		default:
			return RulesExt::Global()->SharedSensors;
		}
	}

	template<typename TExtension>
	inline static void Initialize(typename TExtension::base_type* pParent);

private:
	template <typename T>
	inline void Serialize(T& Stm);
};

template<> struct data_entry<SensorTypeClass>
{
	AbstractTypeClass* OwnerType;
	bool IsEnabled = false;

	ValueableVector<SensorTypeClass*> Types;
	ValueableVector<int> Radiuses;
	ValueableVector<int> Durations;
	ValueableVector<int> Lifetimes;

	//data_entry() = default;
	data_entry(AbstractTypeClass* pOwnerType) : OwnerType(pOwnerType) { }

	virtual void Read(INI_EX& parser, const char* pSection, const char* pPrefix);
	virtual bool Load(PhobosStreamReader& stm, bool registerForChange) { return Serialize(stm); }
	virtual bool Save(PhobosStreamWriter& stm) const { return const_cast<data_entry<SensorTypeClass>*>(this)->Serialize(stm); }

private:
	template <typename T>
	inline bool Serialize(T& stm);
};

template<> struct data_entry_of<SensorTypeClass> { using type = data_entry<SensorTypeClass>; };
