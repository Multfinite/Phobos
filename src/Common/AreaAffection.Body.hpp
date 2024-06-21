#pragma once

#include <list>

#include <Common/AreaAffection.Pre.hpp>

/*!
 * @author Multfinite
 * @brief Use this to perform common actions that affects cells, radiuses, objects in radiuses
*/
namespace AreaAffection
{
	template<typename TAreaAffection>
	struct Logic final
	{
	private:
		Logic() = default;
	public:
		using instance = TAreaAffection;
		static_assert(IsAreaAffection<instance>, "TAreaAffection must qualify to IsAreaAffection concept.");

		using data_entry = typename instance::data_entry;
		static_assert(IsDataEntry<data_entry>, "TAreaAffection::data_entry must qualify to IsDataEntry concept.");
		
		static Logic<instance> Instance;

		/*!
		* @brief For special use-case in PerCellProcess for FootClass, BulletClass
		*/
		void InOut(const data_entry& entry, short radius, int radiusSq
			, CellExt_ExtData* pCurrentExt
			, CellExt_ExtData* pPreviousExt
		)
		{
			for (auto& pItem : entry.Items)
			{
				if (pItem->RadiusSq < radiusSq)
					break; // std::set is sorted

				pItem->Out(pPreviousExt, radius, radiusSq);
				pItem->In(pCurrentExt, radius, radiusSq);
			}
		}
		void In(const data_entry& entry, short radius, int radiusSq, CellExt_ExtData* pExt)
		{
			for (auto& pItem : entry.Items)
			{
				if (pItem->RadiusSq < radiusSq)
					break; // std::set is sorted

				pItem->In(pExt, radius, radiusSq);
			}
		}
		void Out(const data_entry& entry, short radius, int radiusSq, CellExt_ExtData* pExt)
		{
			for (auto& pItem : entry.Items)
			{
				if (pItem->RadiusSq < radiusSq)
					break; // std::set is sorted

				pItem->Out(pExt, radius, radiusSq);
			}
		}
		void ClearInstance(instance* pInst)
		{
			CellExt::IterateRadius(CellClass::Coord2Cell(pInst->GetCenterCoords())
				, pInst->Radius.Get(), pInst->RadiusSq.Get()
				, [&pInst](CellClass* pCell, short radius, int radiusSq)
				{
					pInst->Out(CellExt::ExtMap.Find(pCell), radius, radiusSq);
				});
			instance::Array.remove(pInst);
		}
		void ClearEntry(const data_entry& entry)
		{
			CellStruct position;
			if (auto* pCell = abstract_cast<CellClass*>(entry.Parent))
				position = pCell->MapCoords;
			else
				position = CellClass::Coord2Cell(entry.Parent->GetCenterCoords());
			auto* mostRanged = entry.GetMostRanged();

			CellExt::ForEachCell(position, mostRanged->Radius.Get(), mostRanged->RadiusSq.Get()
			, [this, &entry](short radius, int radiusSq, CellClass* pCell, CellExt_ExtData* pCellExt)
			{
				Out(entry, radius, radiusSq, pCellExt);
			});

			std::for_each(entry.Items.begin(), entry.Items.end(), [](data_entry::instance_ptr& item)
			{
				item->ClearedByEntry = true;
				instance::Array.remove(item.get());
			});
		}
	};

	template<typename ...TAreaAffections>
		requires (IsAreaAffection<TAreaAffections> && ...)
	void MaxRanges(short& radius, int& radiusSq
		, const typename TAreaAffections::data_entry&... entries
	) {
		for (auto& entry : { entries })
		{
			if (entry.Items.empty()) continue;
			auto* pInst = entry.GetMostRanged();

			if (radiusSq < pInst->RadiusSq)
			{
				radius = pInst->Radius;
				radiusSq = pInst->RadiusSq;
			}
		}
	}

	template<typename ...TAreaAffectionsDataEntries>
		requires (IsDataEntry<TAreaAffectionsDataEntries> && ...)
	void MaxRanges(short& radius, int& radiusSq
		, const typename TAreaAffectionsDataEntries&... entries
	)
	{
		for (auto& entry : { entries })
		{
			if (entry.Items.empty()) continue;
			auto* pInst = entry.GetMostRanged();

			if (radiusSq < pInst->RadiusSq)
			{
				radius = pInst->Radius;
				radiusSq = pInst->RadiusSq;
			}
		}
	}

	template<typename ...TAreaAffections>
		requires (IsAreaAffection<TAreaAffections> && ...)
	void In(int radius, int radiusSq
		, CellExt_ExtData* pExt
		, typename TAreaAffections::data_entry&... entries
	) {		
		for (auto& entry : { entries })
		{
			if (entry.Items.empty()) continue;

			using t = typename std::remove_reference_t<decltype(entry)>::instance;
			AreaAffection<t>::Instance.In(entry, radius, radiusSq, pExt);
		}
	}

	template<typename ...TAreaAffections>
		requires (IsAreaAffection<TAreaAffections> && ...)
	void Out(int radius, int radiusSq
		, CellExt_ExtData* pExt
		, typename TAreaAffections::data_entry&... entries
	) {		
		for (auto& entry : { entries })
		{
			if (entry.Items.empty()) continue;

			using t = typename std::remove_reference_t<decltype(entry)>::instance;
			AreaAffection<t>::Instance.Out(entry, radius, radiusSq, pExt);
		}
	}

	template<typename ...TAreaAffections>
		requires (IsAreaAffection<TAreaAffections> && ...)
	void InOut(int radius, int radiusSq
		, CellExt_ExtData* pCurrent, CellExt_ExtData* pPrevious
		, typename TAreaAffections::data_entry&... entries
	)
	{
		for (auto& entry : { entries })
		{
			if (entry.Items.empty()) continue;

			using t = typename std::remove_reference_t<decltype(entry)>::instance;
			AreaAffection<t>::Instance.InOut(entry, radius, radiusSq, pCurrent, pPrevious);
		}
	}

	template<typename TType>
	Instance<TType>::~Instance()
	{
		if (ClearedByEntry) return;
		AreaAffection::Logic<std::remove_pointer_t<decltype(this)>>::Instance.ClearInstance(this);
	}
}
