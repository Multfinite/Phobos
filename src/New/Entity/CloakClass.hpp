#pragma once

#include <Timer.h>
#include <vector>

#include <AbstractClass.h>

#include <Utilities/Enumerable.h>
#include <Utilities/Template.h>
#include <Utilities/GeneralUtils.h>
#include <Utilities/Macro.h>
#include <Utilities/TemplateDef.h>

#include <Common/AreaAffection.hpp>

#include <New/Type/CloakTypeClass.hpp>

class CloakClass : public AreaAffection::Instance
{
public:
	using self = CloakClass;
	using type = CloakTypeClass;

	friend struct AreaAffection::Logic<self>;

	Valueable<type*> Type;

	void* get_underlying_type() const override { return const_cast<type*>(Type.Get()); }

	bool Load(PhobosStreamReader& Stm, bool RegisterForChange) override
	{
		return Instance::Load(Stm, RegisterForChange) && Serialize(Stm);
	}
	bool Save(PhobosStreamWriter& Stm) const override
	{
		auto pThis = const_cast<self*>(this);
		return static_cast<Instance*>(pThis)->Save(Stm) && pThis->Serialize(Stm);
	}
	void remove_from_array() noexcept override
	{
		Array.remove(this);
		Instance::remove_from_array();
	}
private:
	template<typename T>
	bool Serialize(T& Stm)
	{
		return Stm
			.Process(this->Type)
			.Success();
	}
public:
	static std::list<self*> Array;

	bool Self;

	void In(__CellExt_ExtData& cell, short radius, int radiusSq) override;
	void Out(__CellExt_ExtData& cell, short radius, int radiusSq) override;

	CloakClass(CloakTypeClass* type, AbstractClass* parent, HouseClass* owner, short radius);
	~CloakClass();
};

template<> struct data_entry<CloakClass> : public AreaAffection::__data_entry<CloakClass>
{
	ValueableMap<CloakType, std::list<CloakClass*>> ByCloakType;

	data_entry(class AbstractClass* pParent) : AreaAffection::__data_entry<CloakClass>(pParent) { }
};

template<> struct data_entry_of<CloakClass>
{
	using type = data_entry<CloakClass>;
};

static_assert(AreaAffection::IsInstance<CloakClass>, "It is not a Area Affection!");
static_assert(AreaAffection::IsDataEntry<data_entry<CloakClass>>, "It is not an Area Affection data entry!");
