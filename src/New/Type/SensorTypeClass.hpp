#pragma once

#include <Utilities/Enumerable.h>
#include <Utilities/Template.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>
#include <Utilities/TemplateDef.h>

#include <Ext/Rules/Body.h>
#include <TechnoClass.h>
#include <BulletClass.h>

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
		std::string Prefix;
		// will used against this layer
		Valueable<bool> Detect;
		// Show lines like mind reader or TS sensor array
		Valueable<bool> Track;
		Valueable<bool> Decloak;
		// At Radar
		Valueable<bool> Display;

		LayerFlags(const std::string& prefix, bool detect, bool track, bool decloak, bool display) :
			Prefix(prefix), Detect(detect), Track(track), Decloak(decloak), Display(display)
		{}

		virtual void LoadFromINI(CCINIClass* pINI, const char* pSection);
		virtual bool Load(PhobosStreamReader& stm, bool registerForChange);
		virtual bool Save(PhobosStreamWriter& stm) const;

	private:
		template <typename T>
		bool Serialize(T& stm);
	};

	ValueableVector<CloakTypeClass*> Senses;
	Valueable<SensorShareMode> Mode;

	LayerFlags Air, Ground, Subterannean;

	Valueable<bool> Warn;
	Nullable<WeaponTypeClass*> Weapon;
	//NullableIdx<VoxClass> Warn_Eva;

public:
	SensorTypeClass(const char* const pTitle) : Enumerable<SensorTypeClass>(pTitle)
		, Senses { }
		, Mode { SensorShareMode::Default }
		, Air { "Air", true, false, false, false }
		, Ground { "Ground", true, false, false, false }
		, Subterannean { "Subterannean", false, false, false, false }
		, Warn { false }
		, Weapon { }
	{ };

	virtual ~SensorTypeClass() override = default;

	virtual void LoadFromINI(CCINIClass* pINI) override;
	virtual void LoadFromStream(PhobosStreamReader& Stm) override;
	virtual void SaveToStream(PhobosStreamWriter& Stm) override;

	inline bool IsShared() const
	{
		switch (Mode.Get())
		{
		case SensorShareMode::Shared:
			return true;
		case SensorShareMode::Private:
			return false;
		case SensorShareMode::Default:
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

