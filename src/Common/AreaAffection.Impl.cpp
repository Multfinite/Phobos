#include "AreaAffection.hpp"

#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

#include <Common/AreaAffection.Body.hpp>
#include <Common/Entry.Impl.hpp>

#define instantiate_default_impl(instance_class, type_class) declare_instantiate(instance_class, type_class) { return Instantiate_<instance_class, type_class>(owner, type, house, radius); }
#define deinstantiate_default_impl(instance_class, type_class) declare_deinstantiate(instance_class, type_class) { return Deinstantiate_<instance_class, type_class>(owner, instance); }

namespace AreaAffection
{
	template<typename TInstance, typename TType>
	inline constexpr TInstance* Instantiate_(data_entry<TInstance>& owner, TType* type, HouseClass* house, short radius)
	{
		typename decltype(owner.Items)::value_type& inst = owner.Items.emplace_back(
			std::make_unique<decltype(owner.Items)::value_type::element_type>(type, owner.Parent, house, radius
		));
		owner.SortedItems.insert(inst.get());
		if (auto* cell = abstract_cast<CellClass*>(owner.Parent))
			InitializeOnCell(inst.get(), cell);
		return inst.get();
	}

	template<typename TInstance, typename TType>
	inline constexpr bool Deinstantiate_(data_entry<TInstance>& owner, TInstance* instance)
	{
		typename decltype(owner.Items)::iterator it = std::find_if(owner.Items.begin(), owner.Items.end(), [&instance](decltype(owner.Items)::value_type const& x) noexcept { return x.get() == instance; });
		if (it == owner.Items.end())
			return false;
		owner.SortedItems.erase(it->get());
		owner.Items.erase(it);
		return true;
	}

	declare_instantiate(CloakClass, CloakTypeClass)
	{
		decltype(owner.Items)::value_type& inst = owner.Items.emplace_back(
			std::make_unique<decltype(owner.Items)::value_type::element_type>(type, owner.Parent, house, radius
		));
		owner.SortedItems.insert(inst.get());
		owner.ByCloakType[inst->Type->Type].push_back(inst.get());
		if (auto* cell = abstract_cast<CellClass*>(owner.Parent))
			InitializeOnCell(inst.get(), cell);
		return inst.get();
	}
	declare_deinstantiate(CloakClass, CloakTypeClass)
	{
		decltype(owner.Items)::iterator it = std::find_if(owner.Items.begin(), owner.Items.end(), [&instance](decltype(owner.Items)::value_type const& x) noexcept { return x.get() == instance; });
		if (it == owner.Items.end())
			return false;
		owner.ByCloakType[(*it)->Type->Type].remove(it->get());
		owner.SortedItems.erase(it->get());
		owner.Items.erase(it);
		return true;
	}

	instantiate_default_impl(SensorClass, SensorTypeClass);
	deinstantiate_default_impl(SensorClass, SensorTypeClass);

	instantiate_default_impl(ElectronicWarfareClass, ElectronicWarfareTypeClass);
	deinstantiate_default_impl(ElectronicWarfareClass, ElectronicWarfareTypeClass);
}
