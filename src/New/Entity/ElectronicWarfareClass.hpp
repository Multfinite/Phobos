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

#include <New/Type/ElectronicWarfareTypeClass.hpp>

class ElectronicWarfareClass : public AreaAffection::IInstance
{
public:
	using self = ElectronicWarfareClass;
	using type = ElectronicWarfareTypeClass;
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

	ElectronicWarfareClass(ElectronicWarfareTypeClass* type, AbstractClass* parent, HouseClass* owner, short radius) : IInstance(parent, owner, radius)
		, Type(type)
	{
		Array.push_back(this);
	}
	~ElectronicWarfareClass()
	{
		if (ClearedByEntry) return;
		logic::Instance.ClearInstance(this);
	}
};

struct ElectronicWarfareClassDataEntry : public AreaAffection::DataEntry<ElectronicWarfareClass>
{
	using base_type = AreaAffection::DataEntry<ElectronicWarfareClass>;
};

namespace AreaAffection
{
	template<> struct data_entry_of<ElectronicWarfareClass>
	{
		using type = ElectronicWarfareClassDataEntry;
	};
}

static_assert(AreaAffection::IsInstance<ElectronicWarfareClass>, "It is not a Area Affection!");
static_assert(AreaAffection::IsDataEntry<ElectronicWarfareClassDataEntry>, "It is not an Area Affection data entry!")
