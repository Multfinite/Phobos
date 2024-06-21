#include <Common/Processable.hpp>

#include <WaveClass.h>

#include <New/Entity/SensorClass.hpp>
#include <New/Entity/CloakClass.hpp>
#include <New/Entity/ElectronicWarfareClass.hpp>

/*
DEFINE_HOOK(0x55B8F0, Logic_AI_Pre, 0x5)
{

	return 0;
}
*/

/*
DEFINE_HOOK(0x55BA77, Logic_AI_Post, 0x12)
{
	// Original

	auto& waves = *WaveClass::Array;
	for (size_t i = waves.Count - 1; i >= 0; --i)
	{
		auto* pWave = waves.GetItem(i);
		if (pWave->IsInLogic)
			pWave->AI();
	}

	//AI<>();

	return 0x55BA9E;
}
*/
