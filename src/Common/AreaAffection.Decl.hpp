#pragma once
#include <HouseClass.h>

#include "Entry.hpp"

/*
* @author Multfinite
* Current file must contains all **declarations** of
* - template specializations for instance handling;
* - overloads for instance handling.
* All logic functions are global or static.
*/

class SensorClass;
class SensorTypeClass;
class CloakClass;
class CloakTypeClass;
class ElectronicWarfareClass;
class ElectornicWarfareTypeClass;

/*!
* @param type_class literal like Sensor, Cloak, etc...
*/
/*
#define declare_tag(type_class) \
struct type_class##__##tag {}; \
inline static type_class##__##tag type_class##__##tag##_instance{}

#define tag_of(type_class) AreaAffection::type_class##__##tag type_class##__##tag##_instance
#define tag_type_of(type_class) AreaAffection::type_class##__##tag
*/

#define declare_instantiate(instance_class, type_class) instance_class* Instantiate(data_entry<instance_class>& owner, type_class* type, HouseClass* house, short radius)
#define declare_deinstantiate(instance_class) bool Deinstantiate(data_entry<instance_class>& owner, instance_class* instance)

namespace AreaAffection
{
	/*
	declare_tag(SensorClass);
	declare_tag(CloakClass);
	declare_tag(ElectronicWarfareClass);
	*/

	declare_instantiate(SensorClass, SensorTypeClass);
	declare_deinstantiate(SensorClass);

	declare_instantiate(CloakClass, CloakTypeClass);
	declare_deinstantiate(CloakClass);

	declare_instantiate(ElectronicWarfareClass, ElectornicWarfareTypeClass);
	declare_deinstantiate(ElectronicWarfareClass);
}
