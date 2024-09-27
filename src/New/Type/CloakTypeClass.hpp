#pragma once

#include <Utilities/Template.h>
#include <Utilities/TemplateDef.h>
#include <Utilities/Collaborable.hpp>
#include <Utilities/Enumerable.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>

#include <Ext/Rules/Body.h>
#include <TechnoClass.h>
#include <BulletClass.h>

#include <Common/Entry.hpp>

class CloakTypeClass final : public Enumerable<class CloakTypeClass>
{
public:
	using parent_type = AbstractTypeClass;

	struct Layer
	{
		Valueable<bool> Enabled { true };
		NullableIdx<VocClass> SoundIn, SoundOut;

		inline void Read(INI_EX& exINI, const char* pSection, const char* pPrefix);

		template <typename T>
		inline void Serialize(T& Stm);
	};
	template<typename T> struct __group_data
	{
		Valueable<bool> Enabled { false };
		ValueableVector<T*> Allowed, Forbidden;

		inline void Read(INI_EX& parser, const char* pSection, const char* pPrefix)
		{
			Enabled.Read(parser, pSection, string_format("%s.Enabled", pPrefix).c_str());
			Allowed.Read(parser, pSection, string_format("%s.Allowed", pPrefix).c_str());
			Forbidden.Read(parser, pSection, string_format("%s.Forbidden", pPrefix).c_str());
		}

		template<typename T>
		inline void Serialize(T& Stm)
		{
			Stm
				.Process(Enabled)
				.Process(Allowed)
				.Process(Forbidden);
		}
	};
	struct EnemyControl
	{
		Valueable<bool> Enabled { false };
		Valueable<bool> Warn { true };
		NullableIdx<VocClass> Eva;
		Valueable<bool> Raport { true };

		inline void Read(INI_EX& parser, const char* pSection, const char* pPrefix);

		template<typename T>
		inline void Serialize(T& Stm);
	};
	struct Stealth
	{
		ValueableVector<int> Stages;
		ValueableVector<int> Durations;

		inline void Read(INI_EX& parser, const char* pSection);

		template<typename T>
		inline void Serialize(T& Stm);
	};
	struct Disguise
	{
		__group_data<InfantryTypeClass> Infantry;
		__group_data<UnitTypeClass> Vehicles;
		__group_data<UnitTypeClass> Naval;
		__group_data<AircraftTypeClass> Aircraft;
		Valueable<AffectedHouse> Target { AffectedHouse::Enemies };
		struct EnemyControl EnemyControl;

		inline void Read(INI_EX& parser, const char* pSection);

		template<typename T>
		inline void Serialize(T& Stm);
	};
	struct Camouflage
	{
		__group_data<OverlayTypeClass> Overlays;
		Valueable<bool> Sound { false };
		// Sound.Override ??

		inline void Read(INI_EX& parser, const char* pSection);

		template<typename T>
		inline void Serialize(T& Stm);
	};
public:
	Nullable<int> Delay;
	Valueable<bool> InMovement { true };
	Valueable<bool> Shadow { false };
	Valueable<EffectShareMode> Sharing { EffectShareMode::Default };
	Valueable<CloakType> Type { CloakType::Virtual };
	Stealth Stealth;
	Disguise Disguise;
	Camouflage Camouflage;
	Layer Air, Ground, Subterannean;
	Valueable<bool> Warn { false };
	CollaborableIdx<VocClass> WarnEva;

	CloakTypeClass(char const* pTitle) : Enumerable<CloakTypeClass>(pTitle) { };

	virtual ~CloakTypeClass() override = default;

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
			return RulesExt::Global()->SharedCloak;
		}
	}

	template<typename TExtension>
	inline static void Initialize(typename TExtension::base_type* pParent);

private:
	template <typename T>
	inline void Serialize(T& Stm);
};

template<> struct data_entry<CloakTypeClass>
{
	AbstractTypeClass* OwnerType;
	bool IsEnabled = false;

	ValueableVector<CloakTypeClass*> Types;
	ValueableVector<bool> Self;
	ValueableVector<int> Radiuses;
	ValueableVector<AffectedHouse> Targets;

	Nullable<bool> Warn;
	CollaborableIdx<VocClass> WarnEva;

	data_entry(AbstractTypeClass* pOwnerType) : OwnerType(pOwnerType) { }

	virtual void Read(INI_EX& parser, const char* pSection, const char* pPrefix);
	virtual bool Load(PhobosStreamReader& stm, bool registerForChange);
	virtual bool Save(PhobosStreamWriter& stm) const;

private:
	template <typename T>
	bool Serialize(T& stm);
};
template<> struct data_entry_of<CloakTypeClass> { using type = data_entry<CloakTypeClass>; };
