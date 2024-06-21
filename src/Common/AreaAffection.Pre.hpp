#pragma once

#include <memory>

#include <FootClass.h>
#include <HouseClass.h>

#include <Ext/Techno/Body.h>
#include <Ext/TechnoType/Body.h>
#include <Ext/Cell/Body.hpp>

#include <Utilities/Template.h>
#include <Utilities/Stream.h>

#include <Common/AreaAffection.Forward.hpp>

/*!
* @brief All logic for cell radius affection stored here.
* @brief File structure are:
* @brief - AreaAffection.Pre.hpp -- Main definitions: data entry and instance types, concepts. SHOULD NEVER INCLUDE CELL HEADERS - IT IS INCLUDED INTO Ext/Cell/Body.hpp and other area-affected types.
* @brief - AreaAffection.Body.hpp --  All logic which can be separated of specific types of area affections. It is templates-only. Should be used for defining instances of area affectino types. SHOULD BE NEVER INCLUDED INTO CELL and other area-affected types HEADER FILES.
* @brief - AreaAffection.Post.hpp -- Summary of all types, specializations of templated functions 
* @brief - AreaAffection.Entry.hpp -- Declarations for CellExt
* @brief - AreaAffection.cpp
*/
namespace AreaAffection
{
	template<typename T>
	concept IsDataEntry = requires(T x, T* ptr, AbstractClass* abs
		, typename T::instance* pInst, short radius, typename T::instance::type* pType
		, HouseClass* pOwner
	) {
		typename T::instance;
		typename T::instance_ptr;
		typename T::instance::type;
		x.Items; // ValueableSet (based on std::set) which is sorted in descending order
		x.Items.empty(); x.Items.begin(); x.Items.end();
		pInst = x.Instantiate(pType, pOwner, radius);
		abs = x.Parent;
		x = T(abs);
		pInst = x.GetMostRanged();
	};

	template<typename TAreaAffection>
	struct DataEntry
	{
		using instance = TAreaAffection;
		using instance_ptr = std::unique_ptr<instance>;
		using data_entry = DataEntry<instance>;

		/*!
		* @brief Owning instance
		*/
		Valueable<AbstractClass*> Parent;
		ValueableSet<instance_ptr, typename instance::radius_less> Items;
		bool ClearedByEntry = false;

		DataEntry(AbstractClass* pParent) : Parent(pParent) { }

		instance* GetMostRanged() const
		{
			auto& pItem = // unique_ptr
				*(Items.begin()); // std::set is sorted
			return pItem.get();
		}

		instance* Instantiate(typename instance::type* pType, HouseClass* pHouse, short radius)
		{
			instance* pInst = Items.emplace();
			pInst->Parent = Parent;
			pInst->Type = pType;
			pInst->Owner = pHouse;
			pInst->Radius = radius; pInst->RadiusSq = radius ^ 2;
			return pInst;
		}

		bool Load(PhobosStreamReader& stm, bool registerForChange)
		{
			return this->Serialize(stm);
		}
		bool Save(PhobosStreamWriter& stm) const
		{
			return const_cast<data_entry*>(this)->Serialize(stm);
		}

	private:
		template <typename T>
		bool Serialize(T& stm)
		{
			return stm
				.Process(this->Parent)
				.Process(this->Items)
				.Success();
		}
	};

	template<typename T>
	concept IsAreaAffection = requires(T x
		, AbstractClass * abs, HouseClass * house
		, short radius, int radiusSq
		, CellExt_ExtData * cellExt
		, typename T::data_entry * de
		, T * ptr, bool b, CoordStruct coords, HouseClass * pOwner
		, typename T::type * pType
	)
	{
		T::Array; T::Array.empty(); T::Array.begin(); T::Array.end();
		b = x.ClearedByEntry;

		typename T::data_entry;
		typename T::type;

		x.Parent = abs;
		x.Owner = house;
		x.Type = pType;
		x.Radius = radius;
		x.RadiusSq = radiusSq;

		coords = x.GetCenterCoords();
		pOwner = x.GetOwningHouse();

		x.In(cellExt, radius, radiusSq);
		x.Out(cellExt, radius, radiusSq);
	};

	template<typename TType>
	struct Instance
	{
		using type = TType;
		using self = Instance<type>;		
		using data_entry = DataEntry<self>;
		friend struct data_entry;

		using radius_less = RadiusLess<std::unique_ptr<self>>;
		using radius_greater = RadiusGreater<std::unique_ptr<self>>;

		static std::list<self*> Array;
		/*!
		* @brief It is frame-time buffer for all affected objects by current logic. It should be cleared at start of frame.
		*/
		static std::list<AbstractClass*> AffectedObjects;

		Valueable<AbstractClass*> Parent;
		Valueable<HouseClass*> Owner;
		Valueable<type*> Type;
		Valueable<short> Radius;
		Valueable<int> RadiusSq;

		bool HasLifetime = false;
		CDTimerClass LifetimeTimer;

		bool ClearedByEntry = false;
		Instance()
		{
			Array.push_back(this);
		}
		~Instance();

		inline CoordStruct GetCenterCoords() const
		{
			return Parent ? Parent->GetCenterCoords() : CoordStruct::Empty;
		}
		inline HouseClass* GetOwningHouse() const
		{
			return Owner ? Owner : (Parent ? Parent->GetOwningHouse() : nullptr);
		}
		inline bool IsLifetimeOut() const
		{
			return HasLifetime && LifetimeTimer.Completed();
		}

		void In(CellExt_ExtData* cellExt, short radius, int radiusSq);
		void Out(CellExt_ExtData* cellExt, short radius, int radiusSq);
	};

	/*!
	* @brief Use it if parent is known
	*/
	template<typename TAreaAffection, typename TExtension>
	struct Entry
	{
		inline static DataEntry<TAreaAffection>& Of(typename TExtension::ExtData* pExt);
	};

	/*!
	* @brief Use it if parent is unknown
	*/
	template<typename TAreaAffection>
	inline DataEntry<TAreaAffection>* EntryOf(AbstractClass* pAbs);
}
