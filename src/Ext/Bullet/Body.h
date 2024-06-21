#pragma once
#include <BulletClass.h>

#include <Ext/BulletType/Body.h>
#include <Helpers/Macro.h>
#include <Utilities/Container.h>
#include <Utilities/TemplateDef.h>
#include <New/Entity/LaserTrailClass.h>
#include "Trajectories/PhobosTrajectory.h"

#include <Common/AreaAffection.Forward.hpp>

class BulletExt
{
public:
	using base_type = BulletClass;

	static constexpr DWORD Canary = 0x2A2A2A2A;
	static constexpr size_t ExtPointerOffset = 0x18;

	class ExtData final : public Extension<BulletClass>
	{
	public:
		BulletTypeExt::ExtData* TypeExtData;
		HouseClass* FirerHouse;
		int CurrentStrength;
		bool IsInterceptor;
		InterceptedStatus InterceptedStatus;
		bool DetonateOnInterception;
		std::vector<LaserTrailClass> LaserTrails;
		bool SnappedToTarget; // Used for custom trajectory projectile target snap checks
		int DamageNumberOffset;

		PhobosTrajectory* Trajectory; // TODO: why not unique_ptr
		AreaAffection::InstanceEntry* const AreaAffection;

		ExtData(BulletClass* OwnerObject);
		virtual ~ExtData();

		virtual void InvalidatePointer(void* ptr, bool bRemoved) override
		{
			AnnounceInvalidPointer(FirerHouse, ptr);
		}

		virtual void LoadFromStream(PhobosStreamReader& Stm) override;
		virtual void SaveToStream(PhobosStreamWriter& Stm) override;

		void InterceptBullet(TechnoClass* pSource, WeaponTypeClass* pWeapon);
		void ApplyRadiationToCell(CellStruct Cell, int Spread, int RadLevel);
		void InitializeLaserTrails();

	private:
		template <typename T>
		void Serialize(T& Stm);
	};

	class ExtContainer final : public Container<BulletExt>
	{
	public:
		ExtContainer();
		~ExtContainer();

		virtual bool InvalidateExtDataIgnorable(void* const ptr) const override
		{
			auto const abs = static_cast<AbstractClass*>(ptr)->WhatAmI();

			switch (abs)
			{
			case AbstractType::House:
				return false;
			default:
				return true;
			}
		}
	};

	static ExtContainer ExtMap;
};
