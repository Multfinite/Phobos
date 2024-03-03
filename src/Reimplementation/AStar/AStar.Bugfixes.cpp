#include <AStarClass.h>
#include <Utilities/Macro.h>

#include <HouseClass.h>
#include <FootClass.h>
#include <MapClass.h>

constexpr size_t SubzoneTrackingStructSize = sizeof(DynamicVectorClass<SubzoneTrackingStruct>);

#pragma optimize( "", off )
DEFINE_NAKED_HOOK(0x42C4FE, AStar_FindPathHierarchical_Patch)
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

DEFINE_NAKED_HOOK(0x584DE4, MapClass_subzone_Zone_Reset_584550_Patched)
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
#pragma optimize( "", on ) 
