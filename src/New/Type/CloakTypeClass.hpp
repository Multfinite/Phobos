#pragma once

#include <Utilities/Enumerable.h>
#include <Utilities/Template.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>
#include <Utilities/TemplateDef.h>

#include <Ext/Rules/Body.h>
#include <TechnoClass.h>
#include <BulletClass.h>

class CloakClass;
class CloakTypeClass final : public Enumerable<CloakTypeClass>
{
public:
	using parent_type = AbstractTypeClass;
	struct DataEntry
	{
		AbstractTypeClass* OwnerType;
		bool IsEnabled = false;

		NullableVector<CloakTypeClass*> Types;
		NullableVector<boolean> Self;
		NullableVector<int> Radiuses;
		NullableVector<AffectedHouse> Targets;

		Nullable<bool> Warn;
		//NullableIdx<VoxClass> Warn_Eva;
		
		//DataEntry() = default;
		DataEntry(AbstractTypeClass* pOwnerType) : OwnerType(pOwnerType) { }

		virtual void LoadFromINI(CCINIClass* pINI, const char* pSection);
		virtual bool Load(PhobosStreamReader& stm, bool registerForChange);
		virtual bool Save(PhobosStreamWriter& stm) const;

	private:
		template <typename T>
		bool Serialize(T& stm);
	};
	using data_entry = CloakTypeClass::DataEntry;
	friend struct data_entry;

	inline static data_entry* EntryOf(AbstractTypeClass* pAbsType);
	template<typename TExtension>
	inline static data_entry& EntryOf(typename TExtension::ExtData* pExt);

public:
	Valueable<CloakType> Type;
	Valueable<EffectShareMode> Sharing;
	Valueable<bool> Shadow;
	Valueable<bool> Warn;
	//NullableIdx<VoxClass> Warn_Eva;

	CloakTypeClass(const char* const pTitle) : Enumerable<CloakTypeClass>(pTitle)
		, Type(CloakType::Virtual)
		, Sharing(EffectShareMode::Default)
		, Warn { false }
		//, Warn_Eva { }
		, Shadow { false }
	{ };

	virtual ~CloakTypeClass() override = default;

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
			return RulesExt::Global()->SharedCloak;
		}
	}

	template<typename TExtension>
	inline static void Initialize(typename TExtension::base_type* pParent);

private:
	template <typename T>
	void Serialize(T& Stm);
};
