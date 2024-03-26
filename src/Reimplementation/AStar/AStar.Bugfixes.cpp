#include <AStarClass.h>
#include <Utilities/Macro.h>
#include <Utilities/Debug.h>

#include <HouseClass.h>
#include <FootClass.h>
#include <MapClass.h>
#include <CellClass.h>

constexpr size_t SubzoneTrackingStructSize = sizeof(DynamicVectorClass<SubzoneTrackingStruct>);

/*
	CellLevelPassabilityStruct.SubzoneIndex (uint16)
	0x582019
*/

/*
	LevelAndPassabilityStruct2.SubzoneIndex (uint16)
	0x582019
*/

/*
	LevelAndPassabilityStruct2.SubzoneIndex_byPathEnum (uint16[3])
	0x58200F
*/

/*
DEFINE_HOOK(0x42C34A, AStar__FindPathHierarchical_42C34A, 5)
{
	GET_STACK(CellClass*, from, 0x70);
	GET_STACK(CellClass*, to, 0x74);
	GET(int, stage, ESI);

	auto* map = MapClass::Instance.get();

	int fromLinearIndex = map->GetCellIndex_Safe((const CoordStruct&) from->Position);
	int toLinearIndex = map->GetCellIndex_Safe((const CoordStruct&) to->Position);

	auto& fromStruct = map->arrLevelAndPassability2[fromLinearIndex];
	auto& toStruct = map->arrLevelAndPassability2[toLinearIndex];

	Debug::Log("(0x42C34A) Subzone indexes (stage: %d):\nfrom (%d, %d) = %d [%d, %d, %d]\nto (%d, %d) = %d [%d, %d, %d]\n"
		, stage
		, from->Position.X, from->Position.Y, fromLinearIndex, fromStruct.SubzoneIndex_byPathEnum[0], fromStruct.SubzoneIndex_byPathEnum[1], fromStruct.SubzoneIndex_byPathEnum[2]
		, to->Position.X, to->Position.Y, toLinearIndex, toStruct.SubzoneIndex_byPathEnum[0], toStruct.SubzoneIndex_byPathEnum[1], toStruct.SubzoneIndex_byPathEnum[2]
	);

	int fromSubzoneIndex = fromStruct.SubzoneIndex_byPathEnum[stage];
	int toSubzoneIndex = toStruct.SubzoneIndex_byPathEnum[stage];

	R->EBX(fromSubzoneIndex);
	R->Stack<int>(0x34, fromSubzoneIndex);
	R->Stack<int>(0x3C, toSubzoneIndex);

	return 0x42C377;
}
*/

DEFINE_HOOK(0x42C4FE, AStar__FindPathHierarchical_42C4FE, 5)
{
	GET(int, subzoneIndex, ECX);
	GET(int, pathenum, ESI);

	auto* map = MapClass::Instance.get();

	auto& subzones = map->SubzoneTracking[pathenum];

	if (subzoneIndex < 0 || subzoneIndex >= subzones.Count)
	{
		Debug::LogAndMessage("(0x42C4FE) Subzone index: %d (0x%X) must be in range [0; %d)]\n",
			subzoneIndex, subzoneIndex, subzones.Count
		);

		R->EAX(-1);
		R->ECX(0);
		R->EDX(0);
		return 0x42C740;
	}

	auto& subzone = subzones.Items[subzoneIndex];
	auto& connections = subzone.SubzoneConnections;

	R->EAX(subzoneIndex);
	R->ECX(connections.Count);
	R->EDX(connections.Items);
	return connections.Count > 0 ? 0x42C519 : 0x42C740;
}

inline void ResetTracking(MapClass* pThis, int cellIndex, HierarchicalStage stage, int x, int y)
{
	auto& cellInfo = pThis->SubzonesLinking[cellIndex];

	auto& subzonesThis = pThis->SubzoneTracking[stage];
	auto& subzonesNext = pThis->SubzoneTracking[stage + 1];

	int subzoneIndexThis = cellInfo.SubzoneHierarchy[stage];
	int subzoneIndexNext = cellInfo.SubzoneHierarchy[stage + 1];
	if (subzoneIndexThis >= 0 && subzoneIndexThis < subzonesNext.Count)
	{
		subzonesNext.Items[subzoneIndexThis].SubzoneIndex = subzoneIndexNext;
		/*
		Debug::Log("(0x584D5C) Subzone index: %d, stage: %d, indexes: [%d, %d, %d]\n",
			subzoneIndexThis
			, x, y
			, stage
			, cellInfo.SubzoneIndex_byPathEnum[0], cellInfo.SubzoneIndex_byPathEnum[1], cellInfo.SubzoneIndex_byPathEnum[2]
		);
		*/
	}
	else
	{
		Debug::LogAndMessage("(0x584D5C) Subzone index: %d (0x%X) must be in range [0; %d)] at cell (%d, %d), stage: %d, indexes: [%d, %d, %d]\n",
			subzoneIndexThis, subzoneIndexThis, subzonesNext.Count
			, x, y
			, stage
			, cellInfo.SubzoneHierarchy[0], cellInfo.SubzoneHierarchy[1], cellInfo.SubzoneHierarchy[2]
		);
	}
}

DEFINE_HOOK(0x584D5C, MapClass__SubzoneZoneReset_584D5C, 5)
{
	GET(MapClass*, pThis, EBX);
	GET(int, x, ESI);
	GET(int, y, EDI);

	auto cellIndex = pThis->GetCellIndex_Safe(x, y);

	// see 0x567110
	if (cellIndex >= 0 && cellIndex < pThis->ValidMapCellCount)
	{
		ResetTracking(pThis, cellIndex, HierarchicalStage::STAGE_0, x, y);
		ResetTracking(pThis, cellIndex, HierarchicalStage::STAGE_1, x, y);
	}
	else
	{
		Debug::LogAndMessage("(0x584D5C) Cell index is incorrect: %d (0x%X) at (%d, %d), ValidMapCellCount is %d\n",
			cellIndex, cellIndex
			, x, y
			, pThis->ValidMapCellCount
		);
	}
	return 0x584DFE;
}

/*
DEFINE_HOOK(0x584DD6, MapClass__SubzoneZoneReset_584DD6, 5)
{
	GET(int, cellIndex, EAX);
	GET(MapClass*, pThis, EBX);
	GET(int, x, ESI);
	GET(int, y, EDI);

	// see 0x567110
	if (cellIndex >= 0 && cellIndex < pThis->ValidMapCellCount)
	{
		ResetTracking(pThis, cellIndex, PathEnum::PATH_0, x, y);
		ResetTracking(pThis, cellIndex, PathEnum::PATH_1, x, y);
	}
	else
	{
		Debug::LogAndMessage("(0x584DD6) Cell index is incorrect: %d (0x%X) at (%d, %d), ValidMapCellCount is %d\n",
			cellIndex, cellIndex
			, x, y
			, pThis->ValidMapCellCount
		);
	}
	return 0x584DFE;
}
*/

/*
DEFINE_HOOK(0x42C47B, AStar__FindPathHierarchical_42C47B, 7)
{
	GET(int, fromSubzoneIndex, EBX);
	GET(AStarClass*, pThis, EDI);
	GET(int, pathenum, ESI);
	GET_STACK(int*, ints_4C_costs, 0x24);
	GET_STACK(float*, hierarchicalCosts, 0x28);
	GET_STACK(CellClass*, from, 0x70);

	auto* map = MapClass::Instance.get();
	auto& subzones = map->SubzoneTracking[pathenum];

	if (fromSubzoneIndex >= 0 && fromSubzoneIndex < subzones.Count)
	{
		ints_4C_costs[fromSubzoneIndex] = pThis->initedcount;
		hierarchicalCosts[fromSubzoneIndex] = 0.0f;
	}
	else
	{
		Debug::LogAndMessage("(0x42C47B) Subzone index: %d (0x%X) must be in range [0; %d)] at cell (%d, %d)\n",
			fromSubzoneIndex, fromSubzoneIndex, subzones.Count
			, from->Position.X, from->Position.Y
		);
	}

	return 0x42C494;
}
*/

/*
DEFINE_NAKED_HOOK(0x42C4FE, AStar__FindPathHierarchical_Patch)
{
	__asm
	{
		lea eax, [ecx + ecx * 8]
		cmp eax, 0
		jl loc_0x42C740 // index is negative (subzoneIndex < 0)
		mov ecx, [edx + (0x87F874 + 0x10)]
		cmp eax, ecx
		jge loc_0x42C740 // index out of range of vector (subzoneIndex >= vector.Count)
		mov ecx, [edx + (0x87F874 + 0x4)]
		mov edx, [ecx + eax * 4 + 4]
		lea eax, [ecx + eax * 4]
		mov ecx, [eax + 0x10]
		test ecx, ecx
		jle loc_0x42C740
	}
loc_0x42C519:
	__asm
	{
		mov eax, 0x42C519
		jmp eax
	}
loc_0x42C740:
	__asm
	{
		mov eax, 0x42C740
		jmp eax
	}
}

DEFINE_NAKED_HOOK(0x584DE4, MapClass__subzone_Zone_Reset_584550_Patch)
{
	__asm
	{
		movsx ecx, word ptr[eax]
		mov edi, [edx]
		mov bp, [eax + 2]
		lea ecx, [ecx + ecx * 8]
		cmp ecx, 0
		jl skipSubzoneIndex // index is negative (subzoneIndex < 0)
		cmp ecx, [edx + (-0x4+0x10)] // there is some offset because edx is pointer to vector.Vector, but we need vector.Count
		jge skipSubzoneIndex // index out of range of vector (subzoneIndex >= vector.Count)
setSubzoneIndex:
		add edx, 0x18
		add eax, 2
		dec esi
		mov[edi + ecx * 4 + 0x18], bp
		jnz loc_0x584DE4
		jmp loc_0x584DFE
skipSubzoneIndex:
		add edx, 0x18
		add eax, 2
		dec esi
		jnz loc_0x584DE4
		jmp loc_0x584DFE
loc_0x584DE4:
		mov edi, 0x584DE4
		jmp edi
loc_0x584DFE:
		mov edi, 0x584DFE
		jmp edi
	}
}
*/
