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
#include <New/Type/SensorTypeClass.hpp>

class SensorClass : public AreaAffection::IInstance
{
public:
	using self = SensorClass;
	using type = SensorTypeClass;
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

	SensorClass(SensorTypeClass* type, AbstractClass* parent, HouseClass* owner, short radius) : IInstance(parent, owner, radius)
		, Type(type)
	{
		Array.push_back(this);
	}
	~SensorClass()
	{
		if (ClearedByEntry) return;
		logic::Instance.ClearInstance(this);
	}
};

struct SensorClassDataEntry : public AreaAffection::DataEntry<SensorClass> {};

namespace AreaAffection
{
	template<> struct data_entry_of<SensorClass>
	{
		using type = SensorClassDataEntry;
	};
}

static_assert(AreaAffection::IsInstance<SensorClass>, "It is not an Area Affection!");
static_assert(AreaAffection::IsDataEntry<SensorClassDataEntry>, "It is not an Area Affection data entry!")
