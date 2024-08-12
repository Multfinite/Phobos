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

class CloakClass : public AreaAffection::IInstance
{
public:
	using self = CloakClass;
	using type = CloakTypeClass;
	using logic = AreaAffection::Logic<self>;

	friend struct AreaAffection::Logic<self>;

	Valueable<type*> Type;

	void* get_underlying_type() const override { return const_cast<type*>(Type.Get()); }

	bool Load(PhobosStreamReader& Stm, bool RegisterForChange) override
	{
		return IInstance::Load(Stm, RegisterForChange) && Serialize(Stm);
	}
	bool Save(PhobosStreamWriter& Stm) const override
	{
		auto pThis = const_cast<self*>(this);
		return static_cast<IInstance*>(pThis)->Save(Stm) && pThis->Serialize(Stm);
	}
	void remove_from_array() override
	{
		Array.remove(this);
		IInstance::remove_from_array();
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

	CloakClass(CloakTypeClass* type, AbstractClass* parent, HouseClass* owner, short radius) : IInstance(parent, owner, radius)
		, Type(type)
	{
		Array.push_back(this);
	}
	~CloakClass()
	{
		if (ClearedByEntry) return;
		logic::Instance.ClearInstance(this);
	}
};

struct CloakClassDataEntry : public AreaAffection::DataEntry<CloakClass>
{
	ValueableMap<CloakType, std::list<CloakClass*>> ByCloakType;

	void __on_instantiate(instance* pInst) override;
	void __on_deinstantiate(instance* pInst) override;

	CloakClassDataEntry(AbstractClass* pParent) : AreaAffection::DataEntry<CloakClass>(pParent) { }
};

namespace AreaAffection
{
	template<> struct data_entry_of<CloakClass>
	{
		using type = CloakClassDataEntry;
	};
}

static_assert(AreaAffection::IsInstance<CloakClass>, "It is not a Area Affection!");
ert(AreaAffection::IsDataEntry<CloakClassDataEntry>, "It is not an Area Affection data entry!")
