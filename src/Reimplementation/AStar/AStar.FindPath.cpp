#include "AStar.hpp"
#include <MapClass.h>
#include <FootClass.h>
#include <InfantryClass.h>
#include <LocomotionClass.h>

PathType* AStar::FindPath(
	CellStruct* from, CellStruct* to
	, FootClass* object
	, FacingType* way, int maxLoop, MovementZone movementZoneOverride
	, HierarchicalStage stage)
{
	auto* map = MapClass::Instance.get();
	auto* technoType = object->GetTechnoType();

	boolpathfind_38 = true;
	Cleanup();
	for (auto& v : CellIndexesVector)
		v.Clear();

	__Blockage = stage;
	CellClass* fromCell = map->GetCellAt(*from);
	CellClass* toCell = map->GetCellAt(*to);

	auto movementZoneOfObject = movementZoneOverride == MovementZone::None ? technoType->MovementZone : movementZoneOverride;

	auto fromZoneType = map->GetMovementZoneType(*from, movementZoneOfObject, object->OnBridge);
	auto toZoneType = map->GetMovementZoneType(*to, movementZoneOfObject, toCell->ContainsBridge());

	auto src = map->SubzoneBridgeCheck_583180(fromCell, object->OnBridge);
	auto dst = map->SubzoneBridgeCheck_583180(toCell, toCell->ContainsBridge());

	if (object->AbsID == AbstractType::Infantry && technoType->JumpJet)
	{
		auto* inf = (InfantryClass*) object;
		movementZoneOfObject = MovementZone::Infantry;

		void* ppvObject;
		ILocomotion* locomotor = object->Locomotor;
		auto status = locomotor ? locomotor->QueryInterface(__uuidof(IPersist), &ppvObject) : E_POINTER;
		if (status < 0)
			_com_issue_error(status);

	}
	

}
