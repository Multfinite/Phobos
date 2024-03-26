#pragma once

#include <AStarClass.h>

class AStarNeo final
{
private:
	static AStarNeo Instance;
public:
	static AStarNeo& GetInstance() { return Instance; }

	HierarchicalStage Processing;
	DynamicVectorClass<unsigned __int32> CellIndexes[3];

	AStarNeo();
	~AStarNeo();

	PathType* FindPath(
	CellStruct* from, CellStruct* to
	, FootClass* object
	, FacingType* moves, int maxLoop, MovementZone movementZone, HierarchicalStage postProcess);
};

