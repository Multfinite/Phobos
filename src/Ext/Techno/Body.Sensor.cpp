#include "Body.h"

#include <HouseClass.h>
#include <BuildingClass.h>

#include <Ext/Cell/Body.hpp>
#include <Common/AreaAffection.Post.hpp>

bool TechnoExt::ExtData::IsDetectedBy(HouseClass* subject, bool* selectable)
{
	auto* pThis = OwnerObject();
	auto cell = pThis->GetCell();
	auto* cellExt = CellExt::ExtMap.Find(cell);

	auto& cloakEntry = entry<CloakClass>::of<TechnoExt>(*this);

	auto original = [&]() constexpr noexcept -> bool { return cell->Sensors_InclHouse(subject->ArrayIndex);	};

	bool isSensed = false;
	for (auto& instance : cloakEntry.Items)
	{
		auto r = cellExt->AreaAffectionCache->ScanBy(instance->Type, subject);
		try
		{
			auto& g = r->GroupOf(pThis);
			isSensed = isSensed || g.IsDetected() || g.IsDecloaked();
			if (selectable)
				*selectable = *selectable || g.IsSelectable();
		}
		catch (const std::exception& ex)
		{
			return original();
		}
	}

	return isSensed || original();
}
bool TechnoExt::ExtData::IsDecloaked() { throw; }
bool TechnoExt::ExtData::IsDisplayedBy(HouseClass* subject) { throw; }
bool TechnoExt::ExtData::IsTrackedBy(HouseClass* subject) { throw; }
