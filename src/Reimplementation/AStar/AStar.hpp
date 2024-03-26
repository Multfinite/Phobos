#pragma once
#include <AStarClass.h>

class NOVTABLE __declspec(align(4)) AStar
{
public:
	static constexpr reference<AStar, 0x87E8B8> const Instance {};

	char bool_0;
	bool ScaleMovementCost;
	char bool_2;
	char __DoPostProcess;
	float MovementCostScaler;
	char CheckLocomotor;
	AStarWorkPathStructDataHeap* WorkingNodesBuffer;
	AStarWorkPathStructHeap* WorkingNodes;
	PriorityQueueClass<AStarWorkPathStruct>* OpenNodes;
	int* celllevel_costarray2_alt;
	int* celllevel_costarray1;
	float* MovementCosts;
	float* MovementCostsAlt;
	DWORD initedcount;
	DWORD ObjectSpeed;
	int CurrentCellLevel;
	int DestCellLevel;
	bool boolpathfind_38;
	HierarchicalStage __Blockage;
	int* ints_40_costs[3];
	int* ints_4C_costs[3];
	float* HierarchicalCosts[3];
	AStarQueueNodeHierarchical* HierarchicalOpenNodesBuffer;
	PriorityQueueClass<AStarQueueNodeHierarchical>* HierarchicalOpenNodes;
	int CellsProcessed;
	CellStruct CurrentCell;
	DynamicVectorClass<DWORD> CellIndexesVector[3];
	unsigned __int16 somearray_BC[1500];
	int counts_for_subzones_field_C74[3];

	double GetMovementCost(
		  CellClass** from, CellClass** to
		, bool useAlt, MoveType move
		, FootClass* object
	)
	{
		JMP_THIS(0x429830);
	}
	PathType* FindPathRegular(
		  CellStruct* from, CellStruct* to
		, FootClass* object, FacingType* moves
		, signed int maxLoops, HierarchicalStage postProcess
	)
	{
		JMP_THIS(0x429A90);
	}
	AStarWorkPathStruct* CreateNode(
		AStarWorkPathStructNode** pathNodes
		, CellClass** a3, CellStruct* a4
		, float movementCost
	)
	{
		JMP_THIS(0x42A460);
	}
	void Cleanup() { JMP_THIS(0x42A5B0); }
	bool IsSameCostCommon(int a2, char a3, int a4) { JMP_THIS(0x42A690); }
	AStar() { JMP_THIS(0x42A6D0); }
	~AStar() { JMP_THIS(0x42A900); }
	PathType* BuildFinalPathRegular(AStarWorkPathStruct* workPath, FacingType* moves)
	{ JMP_THIS(0x42AA90); }
	void ReinitCostArrays(RectangleStruct* where) { JMP_THIS(0x42AC00); }
	char PostProcessCells(FootClass* object) { JMP_THIS(0x42ACF0); }
	FootClass* GetOccupierRegular(CellStruct* pos, int level) { JMP_THIS(0x42B080); };
	void ProcessFinalPathRegular(PathType* path, FootClass* object) { JMP_THIS(0x42B210); }
	int FixupFinalPathRegular(int a2, CellStruct a3, int a4, int a5, int a6, int a7)
	{ JMP_THIS(0x42B420); }
	void OptimizeFinalPath(PathType* path, FootClass* object) { JMP_THIS(0x42B7F0); }
	void AdjacentCellRegular(FacingType* moves, int a3, int a4, int a5, CellStruct* cellOut)
	{ JMP_THIS(0x42BCA0); }
	bool PlotStraightLineRegular(
		  FacingType* moves, int arg4
		, CellStruct* a4, CellStruct* a5
		, FootClass* object, int* overlap, int a8)
	{
		JMP_THIS(0x42BE20);
	};
	DWORD* ClearPointers() { JMP_THIS(0x42C1C0); }
	bool FindPathHierarchical(
		  CellStruct* from, CellStruct* to
		, MovementZone movementZone, FootClass* object)
	{
		JMP_THIS(0x42C290);
	}
	PathType* FindPath(
		CellStruct* from, CellStruct* to
		, FootClass* object
		, FacingType* way, int maxLoop, MovementZone movementZoneOverride
		, HierarchicalStage stage);

	void InitCellIndexSets(int a2) { JMP_THIS(0x42CCD0); }
	bool IsCellIndexSetRegistered(int xPos, int yPos, int vectorNum) { JMP_THIS(0x42CEB0); }
	void RegisterCellIndexSet(unsigned int xPos, unsigned int yPos, int vectorNum)
	{ JMP_THIS(0x42CF10); }
	void RegisterCellIndexSets(SubzoneTrackingStruct* tracking, HierarchicalStage postProcess)
	{ JMP_THIS(0x42CF80); }
	unsigned int TestCellWalk(CellStruct* a2, CellStruct* a3, FootClass* object, bool bridge1, int bridge2, MovementZone zoneType)
	{ JMP_THIS(0x42D170); }
};

constexpr size_t AStarSize = sizeof(AStar);
static_assert(AStarSize == 0xC80, "AStar size must be C80h (3200d)!");
