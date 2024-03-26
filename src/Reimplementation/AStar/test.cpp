#include <AStarClass.h>
#include <Utilities/Macro.h>

#include <HouseClass.h>
#include <FootClass.h>
#include <MapClass.h>

constexpr size_t SubzoneTrackingStructSize = sizeof(DynamicVectorClass<SubzoneTrackingStruct>);

#pragma optimize( "", off )
void __declspec(naked) AStar_FindPathHierarchical_Original()
{
	// subzoneIndex = EAX
	// subzoneIndex_ = ECX
	// subzoneTrackingOffset_OfPathIndex = EDX
	// subzones_0 = ECX
	// sbznConns = EDX
	// sbznConnsCount = ECX
	__asm
	{
		lea eax, [ecx + ecx * 8] // subzoneIndex = subzoneIndex_
		mov ecx, [edx + 0x87F878] //  ECX = subzones_0 = AStarClass::SubzoneTracking.Items[edx]
		mov edx, [ecx + eax * 4 + 4] // EDX = sbznConns
		lea eax, [ecx + eax * 4]
		mov ecx, [eax + 0x10] // ECX = sbznConnsCount
		test ecx, ecx // sbznConnsCount > 0
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

//DEFINE_NAKED_HOOK(0x42C4FE, AStar_FindPathHierarchical_Patch)
void __declspec(naked) AStar_FindPathHierarchical_Patch()
{
	// subzoneIndex = EAX
	// subzoneIndex_ = ECX
	// subzoneTrackingOffset_OfPathIndex = EDX
	// subzones_0 = ECX
	// sbznConns = EDX
	// sbznConnsCount = ECX
	__asm
	{
		lea eax, [ecx + ecx * 8] // subzoneIndex = subzoneIndex_
		cmp eax, 0
		jl loc_0x42C740
		mov ecx, [edx + (0x87F874 + 0x10)]
		cmp eax, ecx
		jge loc_0x42C740
		mov ecx, [edx + (0x87F874 + 0x4)] //  ECX = subzones_0 = AStarClass::SubzoneTracking.Items[edx]
		mov edx, [ecx + eax * 4 + 4] // EDX = sbznConns
		lea eax, [ecx + eax * 4]
		mov ecx, [eax + 0x10] // ECX = sbznConnsCount
		test ecx, ecx // sbznConnsCount > 0
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

//DEFINE_NAKED_HOOK(0x584DE4, MapClass_subzone_Zone_Reset_584550_Original)
void __declspec(naked) MapClass_subzone_Zone_Reset_584550_Original()
{
	__asm
	{
		movsx ecx, word ptr[eax]
		mov edi, [edx]
		mov bp, [eax + 2]
		lea ecx, [ecx + ecx * 8]
		add edx, 0x18
		add eax, 2
		dec esi
		mov[edi + ecx * 4 + 0x18], bp
		jnz loc_0x584DE4
		jmp loc_0x584DFE
		loc_0x584DE4 :
		mov edi, 0x584DE4
			jmp edi
			loc_0x584DFE :
		mov edi, 0x584DFE
			jmp edi
	}
}

//DEFINE_NAKED_HOOK(0x584DE4, MapClass_subzone_Zone_Reset_584550_Patched)
void __declspec(naked) MapClass_subzone_Zone_Reset_584550_Patched()
{
	__asm
	{
		movsx ecx, word ptr[eax]
		mov edi, [edx]
		mov bp, [eax + 2]
		lea ecx, [ecx + ecx * 8]
		cmp ecx, 0
		jl skipSubzoneIndex
		cmp ecx, [edx + (-0x4 + 0x10)]
		jge skipSubzoneIndex
		//jmp setSubzoneIndex
		setSubzoneIndex :
		add edx, 0x18
			add eax, 2
			dec esi
			mov[edi + ecx * 4 + 0x18], bp
			jnz loc_0x584DE4
			jmp loc_0x584DFE
			skipSubzoneIndex :
		add edx, 0x18
			add eax, 2
			dec esi
			jnz loc_0x584DE4
			jmp loc_0x584DFE
			loc_0x584DE4 :
		mov edi, 0x584DE4
			jmp edi
			loc_0x584DFE :
		mov edi, 0x584DFE
			jmp edi
	}
}
#pragma optimize( "", on ) 
//DEFINE_JUMP(LJMP, 0x42C4FE, GET_OFFSET(AStar_FindPathHierarchical_Patch))

/*
DEFINE_HOOK(0x42C4FE, AStar__FindPathHierarchical_42C4FE, 5)
{
	GET(int, subzoneIndex, ECX); // int - originally
	GET(int, pathenum, ESI);

	//bool isOk = false;
	auto* map = MapClass::Instance.get();

	auto& subzones = map->SubzoneTracking[pathenum];

	if (!subzones.ValidIndex(subzoneIndex) || subzoneIndex < 0)
	{
		R->EAX(-1);
		R->ECX(0);
		R->EDX(0);
		R->ECX(0);
		return 0x42C740;
	}

	auto& subzone = subzones.Items[subzoneIndex];
	auto& connections = subzone.SubzoneConnections;

	R->EAX(subzoneIndex);
	R->ECX(&subzone);
	R->EDX(connections.Items);
	R->ECX(connections.Count);

	return connections.Count > 0 ? 0x42C519 : 0x42C740;
}
*/

/*
// error at 0x584DF7
DEFINE_HOOK(0x584DFC, MapClass__SubzoneZoneReset_584DFC, 5)
{
	GET(int, i, ESI);
	GET(__int16*, subzoneIndex_byPathEnum, EAX);
	GET(SubzoneTrackingStruct**, arrSubzonesDVC, EDX);

	do
	{
		auto arrSubzones = *arrSubzonesDVC;
		auto currentSubzoneIndex = subzoneIndex_byPathEnum[0];
		auto subzoneIndex = subzoneIndex_byPathEnum[1];
		DynamicVectorClass<SubzoneTrackingStruct>* dvc = (DynamicVectorClass<SubzoneTrackingStruct>*)(((char*)arrSubzonesDVC) - 0x4);
		if(currentSubzoneIndex >= 0 && dvc->ValidIndex(currentSubzoneIndex))
			arrSubzones[currentSubzoneIndex].SubzoneIndex = subzoneIndex;

		arrSubzonesDVC = (SubzoneTrackingStruct**)(((char*)arrSubzonesDVC) + sizeof(DynamicVectorClass<SubzoneConnectionStruct>));
		++subzoneIndex_byPathEnum;
	}
	while (--i); // 2 = (1 > 0), 1 = (0 > 0). So real i = [2, 1]
	//return 0x584DFE;

	R->EDI(R->Stack<int>(0x24));
	R->EBP(R->Stack<int>(0x38));
	R->ESI(R->Stack<int>(0x20));

	return 0x584E0A;
}
*/

//DEFINE_JUMP(LJMP, 0x584DD6, 0x584DFE);

inline void ResetSubzones(MapClass* pMap, int cellIndex, int path)
{
	int i = 2 - path;
	auto& subzones = pMap->SubzoneTracking[i];
	auto& subzoneIndexes = pMap->SubzonesLinking[cellIndex].SubzoneHierarchy;

	int subzoneIndex = subzoneIndexes[i + 1];
	int currentSubzoneIndex = subzoneIndexes[i + 0];

	subzones.Items[currentSubzoneIndex].SubzoneIndex = subzoneIndex;
}
/*
DEFINE_HOOK(0x584DD6, AStar_FindPathHierarchical_584DD6, 8)
{
	GET(MapClass*, pMap, EBX);
	GET(int, cellIndex, EAX);

	pMap->SubzoneTracking[1].Items[pMap->arrLevelAndPassability2[cellIndex].SubzoneIndex_byPathEnum[1]]
		.SubzoneIndex =
		pMap->arrLevelAndPassability2[cellIndex].SubzoneIndex_byPathEnum[2];

	pMap->SubzoneTracking[2].Items[pMap->arrLevelAndPassability2[cellIndex].SubzoneIndex_byPathEnum[2]]
		.SubzoneIndex =
		pMap->arrLevelAndPassability2[cellIndex].SubzoneIndex_byPathEnum[3];

	return 0x584DFE;
}
*/

/*
// AStar: regular queue
DEFINE_PATCH_TYPED(DWORD, 0x42A763, 4 * 10000); // capacity
DEFINE_PATCH_TYPED(DWORD, 0x42A750, 4 * 0x40004); // new
// AStar: hierarchical queue
DEFINE_PATCH_TYPED(DWORD, 0x42A7B5, 4 * 0x2710); // capacity
DEFINE_PATCH_TYPED(DWORD, 0x42A7A2, 4 * 0x9C44); // new
// AStar: hierarchical queue buffer
DEFINE_PATCH_TYPED(DWORD, 0x42A8E1, 4 * 0x27100);
*/
