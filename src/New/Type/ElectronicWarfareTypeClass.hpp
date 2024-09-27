#pragma once

#include <Utilities/Enumerable.h>
#include <Utilities/Template.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>
#include <Utilities/TemplateDef.h>

#include <Ext/Rules/Body.h>
#include <TechnoClass.h>
#include <BulletClass.h>

#include <Common/Entry.hpp>

class ElectronicWarfareTypeClass : public Enumerable<ElectronicWarfareTypeClass>
{
public:
	using parent_type = AbstractTypeClass;

public:
	ElectronicWarfareTypeClass(const char* const pTitle) : Enumerable<ElectronicWarfareTypeClass>(pTitle)
	{ };

	virtual ~ElectronicWarfareTypeClass() override = default;

	virtual void LoadFromINI(CCINIClass* pINI) override;
	virtual void LoadFromStream(PhobosStreamReader& Stm) override;
	virtual void SaveToStream(PhobosStreamWriter& Stm) override;

	template<typename TExtension>
	inline static void Initialize(typename TExtension::base_type* pParent);
private:
	template <typename T>
	void Serialize(T& Stm);
};

template<> struct data_entry<ElectronicWarfareTypeClass>
{
	AbstractTypeClass* OwnerType;
	bool IsEnabled = false;

	ValueableVector<ElectronicWarfareTypeClass*> Types;
	ValueableVector<AffectedHouse> Targets;
	ValueableVector<int> Radiuses;
	ValueableVector<int> Durations;
	ValueableVector<int> Lifetime;
	ValueableVector<bool> Indiscriminate;
	ValueableVector<bool> AsPassenger;
	ValueableVector<bool> AsOccupant;

	//data_entry() = default;
	data_entry(AbstractTypeClass* pOwnerType) : OwnerType(pOwnerType) { }

	virtual void LoadFromINI(CCINIClass* pINI, const char* pSection);
	virtual bool Load(PhobosStreamReader& stm, bool registerForChange);
	virtual bool Save(PhobosStreamWriter& stm) const;

private:
	template <typename T>
	bool Serialize(T& stm);
};
template<> struct data_entry_of<ElectronicWarfareTypeClass> { using type = data_entry<ElectronicWarfareTypeClass>; };
