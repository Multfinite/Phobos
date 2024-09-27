#pragma once

#include <Common/AreaAffection.hpp>

#include <Ext/Cell/Body.hpp>

namespace AreaAffection
{
	template<typename TInstance>
	void Logic<TInstance>::InOut(data_entry_t const& entry, short radius, int radiusSq
		, __CellExt_ExtData* pCurrentExt
		, __CellExt_ExtData* pPreviousExt
	) {
		for (auto& pItem : entry.SortedItems)
		{
			if (pItem->RadiusSq < radiusSq)
				break; // std::set is sorted

			pItem->Out(*pPreviousExt, radius, radiusSq);
			pItem->In(*pCurrentExt, radius, radiusSq);
		}
	}

	template<typename TInstance>
	void Logic<TInstance>::In(data_entry_t const& entry, short radius, int radiusSq, __CellExt_ExtData* pExt)
	{
		for (auto& pItem : entry.SortedItems)
		{
			if (pItem->RadiusSq < radiusSq)
				break; // std::set is sorted

			pItem->In(*pExt, radius, radiusSq);
		}
	}

	template<typename TInstance>
	void Logic<TInstance>::Out(data_entry_t const& entry, short radius, int radiusSq, __CellExt_ExtData* pExt)
	{
		for (auto& pItem : entry.SortedItems)
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
			, [&pInst](CellClass* pCell, short radius, int radiusSq) constexpr
			{
				pInst->Out(*CellExt::ExtMap.Find(pCell), radius, radiusSq);
			});
		pInst->remove_from_array();
	}

	template<typename TInstance>
	void Logic<TInstance>::ClearEntry(data_entry_t const& entry)
	{
		CellStruct position;
		if (auto* pCell = abstract_cast<CellClass*>(entry.Parent))
			position = pCell->MapCoords;
		else
			position = CellClass::Coord2Cell(entry.Parent->GetCenterCoords());
		auto* mostRanged = entry.GetMostRanged();

		CellExt::ForEachCell(position, mostRanged->Radius.Get(), mostRanged->RadiusSq.Get()
		, [this, &entry](short radius, int radiusSq, CellClass* pCell, CellExt::ExtData* pCellExt) constexpr
		{
			Out(entry, radius, radiusSq, pCellExt);
		});

		std::for_each(entry.Items.begin(), entry.Items.end(), [](data_entry::instance_ptr& item) constexpr
		{
			item->ClearedByEntry = true;
			item->remove_from_array();
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

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void In(short radius, int radiusSq
		, __CellExt_ExtData* pExt
		, typename TDataEntries&... entries
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

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void Out(short radius, int radiusSq
		, __CellExt_ExtData* pExt
		, typename TDataEntries&... entries
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
	void InOut(short radius, int radiusSq
		, __CellExt_ExtData* pCurrent, __CellExt_ExtData* pPrevious
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
}
