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

class CloakTypeClass;

class SensorClass;
class SensorTypeClass final : public Enumerable<SensorTypeClass>
{
public:
	using parent_type = AbstractTypeClass;
	struct DataEntry
	{
		parent_type* OwnerType;
		bool IsEnabled = false;

		NullableVector<SensorTypeClass*> Types;
		NullableVector<int> Radiuses;
		NullableVector<int> Durations;
		NullableVector<int> Lifetimes;

		//DataEntry() = default;
		DataEntry(AbstractTypeClass* pOwnerType) : OwnerType(pOwnerType) { }

		virtual void LoadFromINI(CCINIClass* pINI, const char* pSection);
		virtual bool Load(PhobosStreamReader& stm, bool registerForChange);
		virtual bool Save(PhobosStreamWriter& stm) const;

	private:
		template <typename T>
		bool Serialize(T& stm);
	};
	using data_entry = SensorTypeClass::DataEntry;
	friend struct data_entry;

	inline static data_entry* EntryOf(AbstractTypeClass* pAbsType);
	template<typename TExtension>
	inline static data_entry& EntryOf(typename TExtension::ExtData* pExt);

	struct LayerFlags
	{
		/*!
		* @brief Prefix of key in INI file
		*/
		std::string Prefix;
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

		LayerFlags(const std::string& prefix, bool detect, bool track, bool decloak, bool display) :
			Prefix(prefix), Scan(detect), Track(track), Decloak(decloak), Display(display)
		{}

		virtual void LoadFromINI(CCINIClass* pINI, const char* pSection);
		virtual bool Load(PhobosStreamReader& stm, bool registerForChange);
		virtual bool Save(PhobosStreamWriter& stm) const;

		inline bool HasEffect() const { return Scan || Track || Decloak || Display || Weapon || Animation; }

	private:
		template <typename T>
		bool Serialize(T& stm);
	};

	ValueableVector<CloakTypeClass*> Scan;
	Valueable<EffectShareMode> Sharing;
	/*!
	* @brief Controls how cloak vs sensor conflict will be solved.
	* @brief If enabled then object became sensed if any cloak types from `Senses` present.
	* @brief If disabled then object became sensed if all cloaks presented in `Senses` list.
	*/
	Valueable<bool> IsStrong;
	Valueable<bool> Selectable;

	Valueable<int> Delay, Duration, CellIncrement;

	LayerFlags Air, Ground, Subterannean;

	Valueable<bool> ForceShadows, InMovement;

	Valueable<bool> Warn;
	NullableIdx<VocClass*> Warn_Eva;
	ValueableMap<SideClass*, VocClass*> Warn_Eva_Sides;
	ValueableMap<HouseTypeClass*, VocClass*> Warn_Eva_Countries;

	//NullableIdx<VoxClass> Warn_Eva;

	VoxClass* GetWarn(SideClass* side, HouseTypeClass* country) const;
public:
	SensorTypeClass(const char* const pTitle) : Enumerable<SensorTypeClass>(pTitle)
		, Scan { }
		, Sharing { EffectShareMode::Default }
		, IsStrong { true }, Selectable { false }
		, Air { "Air", true, false, false, false }
		, Ground { "Ground", true, false, false, false }
		, Subterannean { "Subterannean", false, false, false, false }
		, Warn { false }
	{ };

	virtual ~SensorTypeClass() override = default;

	virtual void LoadFromINI(CCINIClass* pINI) override;
	virtual void LoadFromStream(PhobosStreamReader& Stm) override;
	virtual void SaveToStream(PhobosStreamWriter& Stm) override;

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
	void Serialize(T& Stm);
};

