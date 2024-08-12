#pragma once

#include <CCINIClass.h>
#include <CellClass.h>
#include <GameStrings.h>
#include <Helpers/Macro.h>
#include <Utilities/Macro.h>
#include <Utilities/Container.h>
#include <Utilities/Constructs.h>
#include <Utilities/Template.h>
#include <Utilities/Enum.h>
#include <Utilities/TemplateDef.h>
#include <Utilities/Debug.h>

#include <Common/Common.hpp>
#include <Common/AreaAffection.hpp>

class __CellExt_ExtData final : public Extension<CellClass>
{
public:
	AreaAffection::CellEntry* const AreaAffectionCache;
	AreaAffection::InstanceEntry* const AreaAffection;

	__CellExt_ExtData(CellClass* ownerObject);
	virtual ~__CellExt_ExtData();

	virtual void LoadFromINIFile(CCINIClass* pINI) override;
	virtual void LoadBeforeTypeData(RulesClass* pThis, CCINIClass* pINI);
	virtual void LoadAfterTypeData(RulesClass* pThis, CCINIClass* pINI);
	virtual void InitializeConstants() override;
	void InitializeAfterTypeData(RulesClass* pThis);

	virtual void InvalidatePointer(void* ptr, bool bRemoved) override;

	virtual void LoadFromStream(PhobosStreamReader& Stm) override;
	virtual void SaveToStream(PhobosStreamWriter& Stm) override;

	template<typename THandler> requires ItemHandler<THandler, ObjectClass*>
	inline void IterateObjects(const THandler& handler)
	{
		auto pObject = OwnerObject()->FirstObject;
		while (pObject != nullptr)
		{
			handler(pObject);
			pObject = pObject->NextObject;
		}
	}
private:
	template <typename T>
	bool Serialize(T& Stm)
	{
		return Stm
			.Process(*this->AreaAffectionCache)
			.Process(*this->AreaAffection)
			.Success();
	}
};

class CellExt
{
public:
	using base_type = CellClass;

	static constexpr DWORD Canary = 0x91828291;
	static constexpr size_t ExtPointerOffset = 0x144;

	using ExtData = __CellExt_ExtData;

	class ExtContainer final : public Container<CellExt>
	{
	public:
		ExtContainer();
		~ExtContainer();
	};

	static ExtContainer ExtMap;

	static bool LoadGlobals(PhobosStreamReader& Stm);
	static bool SaveGlobals(PhobosStreamWriter& Stm);

	template<typename THandler> requires ItemHandler<THandler, CellClass*, short, int>
	inline static void IterateRadius(CellStruct where, short radius, int radiusSquared, const THandler& handler)
	{
		radius = radius < 0 ? -radius : radius;
		for (short x = -radius; x <= radius; x++)
			for (short y = -radius; y <= radius; y++)
			{
				auto cellPosition = where + CellStruct { x, y };
				auto radiusSq = static_cast<int>(where.DistanceFromSquared(cellPosition));
				if (radiusSq > radiusSquared)
					continue;
				auto* pCell = MapClass::Instance->GetCellAt(cellPosition);
				handler(pCell, radius, radiusSq);
			}
	}

	// TODO: 1 implement chaching of CellStruct per each Radius level
	// TODO: 2 in some cases we can try to use threads if have enoguh cell count (need investigation)
	template<typename THandler> requires ItemHandler<THandler, CellStruct, short, int>
	inline static void GenerateRadius(short radius, int radiusSquared, const THandler& handler)
	{
		constexpr auto where = CellStruct::Empty;
		radius = radius < 0 ? -radius : radius;
		for (short x = -radius; x <= radius; x++)
			for (short y = -radius; y <= radius; y++)
			{
				auto cellPosition = CellStruct { x, y };
				auto radiusSq = static_cast<int>(where.DistanceFromSquared(cellPosition));
				if (radiusSq > radiusSquared)
					continue;
				handler(cellPosition, radius, radiusSq);
			}
	}

	template<typename THandler>
		requires ItemHandler<THandler,
			short, /* radiusq */
			int,  /* radiusSq */
			CellClass*, /* pCurrent */
			CellExt::ExtData*,
			CellClass*, /* pPrevious */
			CellExt::ExtData*
		>
	inline static void ForEachCell(short radius, int radiusSquared, CellStruct currentMapCoords, CellStruct lastMapCoords, const THandler& handler)
	{	
		CellExt::GenerateRadius(radius, radiusSquared, [&](CellStruct r, short radius, int radiusSq)
		{
			auto previousPosition = lastMapCoords + r;
			auto currentPosition = currentMapCoords + r;
	
			CellClass* pPrevious = MapClass::Instance->GetCellAt(previousPosition);
			CellClass* pCurrent = MapClass::Instance->GetCellAt(currentPosition);
	
			auto* pPreviousExt = CellExt::ExtMap.Find(pPrevious);
			auto* pCurrentExt = CellExt::ExtMap.Find(pCurrent);
	
			handler(radius, radiusSq, pCurrent, pCurrentExt, pPrevious, pPreviousExt);
		});
	}
	
	template<typename THandler>
		requires ItemHandler<THandler
			, int /* radius */
			, int  /* radiusSq */
			, CellClass* /* pCell */
			, CellExt::ExtData*
		>
	inline static void ForEachCell(CellStruct mapCoords, short radius, int radiusSquared, const THandler& handler)
	{
		CellExt::GenerateRadius(radius, [&](CellStruct r, short radius, int radiusSq)
		{
			auto position = mapCoords + r;	
			CellClass* pCell = MapClass::Instance->GetCellAt(position);	
			auto* pCellExt = CellExt::ExtMap.Find(pCell);	
			handler(radius, radiusSq, pCell, pCellExt);
		});
	}
	
	template<typename THandler> requires ItemHandler<THandler, ObjectClass*, CellExt::ExtData*>
	inline static void ObjectsInRadius(CellStruct where, short radius, int radiusSquared, const THandler& objectHandler)
	{
		auto handler = [&objectHandler](CellClass* pCell) -> void
		{
			auto* pCellExt = CellExt::ExtMap.Find(pCell);
			auto handler = [&pCellExt, &objectHandler](ObjectClass* pObject) -> void
			{
				objectHandler(pObject, pCellExt);
			};
			pCellExt->IterateObjects<decltype(handler)>(handler);
		};
		IterateRadius<decltype(handler)>(where, radius, radiusSquared, handler);
	}
};
