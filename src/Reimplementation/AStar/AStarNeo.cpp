#include "AStarNeo.h"

#include <MapClass.h>
#include <FootClass.h>

#include <Utilities/Macro.h>

AStarNeo AStarNeo::Instance {};

AStarNeo::AStarNeo() = default;
AStarNeo::~AStarNeo() = default;

PathType* AStarNeo::FindPath(
	CellStruct* from, CellStruct* to
	, FootClass* object
	, FacingType* moves, int maxLoop, MovementZone movementZoneOverride, HierarchicalStage postProcess)
{
	auto* map = MapClass::Instance.get();

	for (auto& v : CellIndexes)
		v.Clear();

	Processing = postProcess;
	CellClass* fromCell = map->GetCellAt((const CellStruct&) from);
	CellClass* toCell = map->GetCellAt((const CellStruct&) to);

	auto movementZoneOfObject = movementZoneOverride != MovementZone::None ? movementZoneOverride : object->GetTechnoType()->MovementZone;
	auto fromMovementZoneType = map->GetMovementZoneType((const CellStruct&)from, movementZoneOfObject, object->OnBridge);
	auto toMovementZoneType = map->GetMovementZoneType((const CellStruct&) to, movementZoneOfObject, toCell->ContainsBridge());

	return nullptr;
}
