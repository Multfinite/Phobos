#pragma once

#include <Common/AreaAffection.hpp>

#include <Ext/Cell/Body.hpp>

namespace AreaAffection
{
	template<typename TInstance>
	void Logic<TInstance>::InOut(const data_entry& entry, short radius, int radiusSq
		, CellExt::ExtData* pCurrentExt
		, CellExt::ExtData* pPreviousExt
	)
	{
		for (auto& pItem : entry.Items)
		{
			if (pItem->RadiusSq < radiusSq)
				break; // std::set is sorted

			pItem->Out(*pPreviousExt, radius, radiusSq);
			pItem->In(*pCurrentExt, radius, radiusSq);
		}
	}

	template<typename TInstance>
	void Logic<TInstance>::In(const data_entry& entry, short radius, int radiusSq, CellExt::ExtData* pExt)
	{
		for (auto& pItem : entry.Items)
		{
			if (pItem->RadiusSq < radiusSq)
				break; // std::set is sorted

			pItem->In(*pExt, radius, radiusSq);
		}
	}

	template<typename TInstance>
	void Logic<TInstance>::Out(const data_entry& entry, short radius, int radiusSq, CellExt::ExtData* pExt)
	{
		for (auto& pItem : entry.Items)
		{
			if (pItem->RadiusSq < radiusSq)
				break; // std::set is sorted

			pItem->Out(*pExt, radius, radiusSq);
		}
	}

	template<typename TInstance>
	void Logic<TInstance>::ClearInstance(instance* pInst)
	{
		CellExt::IterateRadius(CellClass::Coord2Cell(pInst->GetCenterCoords())
			, pInst->Radius.Get(), pInst->RadiusSq.Get()
			, [&pInst](CellClass* pCell, short radius, int radiusSq)
			{
				pInst->Out(*CellExt::ExtMap.Find(pCell), radius, radiusSq);
			});
		instance::Array.remove(pInst);
	}

	template<typename TInstance>
	void Logic<TInstance>::ClearEntry(const data_entry& entry)
	{
		CellStruct position;
		if (auto* pCell = abstract_cast<CellClass*>(entry.Parent))
			position = pCell->MapCoords;
		else
			position = CellClass::Coord2Cell(entry.Parent->GetCenterCoords());
		auto* mostRanged = entry.GetMostRanged();

		CellExt::ForEachCell(position, mostRanged->Radius.Get(), mostRanged->RadiusSq.Get()
		, [this, &entry](short radius, int radiusSq, CellClass* pCell, CellExt::ExtData* pCellExt)
		{
			Out(entry, radius, radiusSq, pCellExt);
		});

		std::for_each(entry.Items.begin(), entry.Items.end(), [](data_entry::instance_ptr& item)
		{
			item->ClearedByEntry = true;
			instance::Array.remove(item.get());
		});
	}

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void MaxRanges(short& radius, int& radiusSq
		, typename TDataEntries const&... entries
	) {
		([&]
		{
			if (!entries.Items.empty())
			{
				auto* pInst = entries.GetMostRanged();

				if (radiusSq < pInst->RadiusSq)
				{
					radius = pInst->Radius;
					radiusSq = pInst->RadiusSq;
				}
			}
		}(), ...);
	}

	template<typename ...TInstance>
		requires (IsInstance<TInstance> && ...)
	void In(int radius, int radiusSq
		, CellExt::ExtData* pExt
		, typename TInstance::data_entry&... entries
	) {
		([&]
		{
			if (!entries.Items.empty())
			{
				using t = typename std::remove_reference_t<decltype(entries)>::instance;
				AreaAffection::Logic<t>::Instance.In(entries, radius, radiusSq, pExt);
			}
		}(), ...);
	}

	template<typename ...TInstance>
		requires (IsInstance<TInstance> && ...)
	void Out(int radius, int radiusSq
		, CellExt::ExtData* pExt
		, typename TInstance::data_entry&... entries
	) {
		([&]
		{
			if (!entries.Items.empty())
			{
				using t = typename std::remove_reference_t<decltype(entries)>::instance;
				AreaAffection::Logic<t>::Instance.Out(entries, radius, radiusSq, pExt);
			}
		}(), ...);
	}

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void InOut(int radius, int radiusSq
		, CellExt::ExtData* pCurrent, CellExt::ExtData* pPrevious
		, typename TDataEntries&... entries
	) {
		([&]
		{
			if (!entries.Items.empty())
			{
				using t = typename std::remove_reference_t<decltype(entries)>::instance;
				AreaAffection::Logic<t>::Instance.InOut(entries, radius, radiusSq, pCurrent, pPrevious);
			}
		}(), ...);
	}

	template<typename TType, typename TDataEntry>
	Instance<TType, TDataEntry>::~Instance()
	{		
		if (ClearedByEntry) return;
		AreaAffection::Logic<std::remove_pointer_t<decltype(this)>>::Instance.ClearInstance(this);
	}
}
