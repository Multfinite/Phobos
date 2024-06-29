#pragma once

#include <memory>
#include <list>

#include <AbstractClass.h>
#include <FootClass.h>
#include <HouseClass.h>
#include <CellClass.h>

#include <Utilities/Template.h>
#include <Utilities/Stream.h>
#include <Utilities/Misc.hpp>

struct __CellExt_ExtData;

/*!
* @brief All logic for cell radius affection stored here.
* @brief File structure are:
*/
namespace AreaAffection
{
	template<typename TAreaAffection> struct Logic;
	struct InstanceEntry;
	struct CellEntry;

	template<typename T>
	concept IsDataEntry = requires(T x, T * ptr, AbstractClass * abs
		, typename T::instance * pInst, short radius, typename T::instance::type * pType
		, HouseClass * pOwner
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

	template<typename TInstance>
	struct DataEntry
	{
		using instance = TInstance;
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
	concept IsInstance = requires(T x
		, AbstractClass * abs, HouseClass * house
		, short radius, int radiusSq
		, __CellExt_ExtData& cell
		, typename T::data_entry * de
		, T * ptr, bool b, CoordStruct coords, HouseClass * pOwner
		, typename T::type * pType
	) {
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

		x.In(cell, radius, radiusSq);
		x.Out(cell, radius, radiusSq);
	};

	/*!
	* @author Multfinite
	* @brief Interface for any area affection instance.
	* @bruef It links area affection type and it's owner.
	*/
	struct IInstance
	{
		struct radius_less
		{
			bool operator() (IInstance const& lhs, IInstance const& rhs) const { return lhs.Radius < rhs.Radius; }
			bool operator() (IInstance const* lhs, IInstance const* rhs) const { return lhs->Radius < rhs->Radius; }
		};
		struct radius_greater
		{
			bool operator() (IInstance const& lhs, IInstance const& rhs) const { return lhs.Radius > rhs.Radius; }
			bool operator() (IInstance const* lhs, IInstance const* rhs) const { return lhs->Radius > rhs->Radius; }
		};

		static std::list<IInstance*> Array;

		/*!
		 * @brief This area affection instance source of center coordinates and behavior.
		 * @brief On common it should be TechnoClass, BulletClass, CellClass.
		 */
		Valueable<AbstractClass*> Parent;

		/*!
		 * @brief The owner house.
		 */
		Valueable<HouseClass*> Owner;

		/*!
		 * @brief Non-typed pointer to area affection type.
		 */
		virtual void* get_underlying_type() const = 0;

		/*!
		 * @brief Radius in cells.
		 */
		Valueable<short> Radius;

		/*!
		 * @brief Pre-calculated `radius ^ 2`.
		 */
		Valueable<int> RadiusSq;

		inline CoordStruct GetCenterCoords() const
		{
			return Parent ? Parent->GetCenterCoords() : CoordStruct::Empty;
		}
		inline HouseClass* GetOwningHouse() const
		{
			return Owner ? Owner : (Parent ? Parent->GetOwningHouse() : nullptr);
		}

		/*!
		 * @brief Affects given cell. This allowed to generate cache.
		 * @note To understand what happens here see `VanillaSensorClass`
		 */
		virtual void In(__CellExt_ExtData& cell, short radius, int radiusSq) = 0;
		/*!
		 * @brief Unaffects given cell. This should remove generated cache of `IInstance::In`.
		 */
		virtual void Out(__CellExt_ExtData& cell, short radius, int radiusSq) = 0;

		virtual bool Load(PhobosStreamReader& Stm, bool RegisterForChange)
		{
			return Serialize(Stm);
		}
		virtual bool Save(PhobosStreamWriter& Stm) const
		{
			return const_cast<IInstance*>(this)->Serialize(Stm);
		}
	protected:
		IInstance(AbstractClass* parent, HouseClass* owner, short radius) :
			Parent(parent), Owner(owner), Radius(radius), RadiusSq(radius ^ 2)
		{
			Array.push_back(this);
		}
		~IInstance() { Array.remove(this); }
	private:
		template<typename T>
		bool Serialize(T& Stm)
		{
			return Stm
				.Process(this->Parent)
				.Process(this->Owner)
				.Process(this->Radius)
				.Process(this->RadiusSq)
				.Success();
		}
	};

	template<typename TType, typename TDataEntry>
	struct Instance : public IInstance
	{
		using type = TType;
		using data_entry = TDataEntry;
		using self = Instance<type, data_entry>;		

		static std::list<self*> Array;

		Valueable<type*> Type;

		void* get_underlying_type() const override { return const_cast<type*>(Type.Get()); }

		bool Load(PhobosStreamReader& Stm, bool RegisterForChange) override
		{
			return IInstance::Load(Stm, RegisterForChange) && Serialize(Stm);
		}
		bool Save(PhobosStreamWriter& Stm) const override
		{
			auto pThis = const_cast<self*>(this);
			return static_cast<IInstance*>(pThis)->Save(Stm) && pThis->Serialize(Stm);
		}

		friend class AreaAffection::Logic<self>;
		bool ClearedByEntry = false;
	protected:
		Instance(type* type, AbstractClass* parent, HouseClass* owner, short radius) :
			IInstance(parent, owner, radius), Type(type)
		{
			Array.push_back(this);
		}
		~Instance();
	private:
		template<typename T>
		bool Serialize(T& Stm)
		{
			return Stm
				.Process(this->Type)
				.Success();
		}
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

	/*!
	* @brief Common generalized logic.
	*/
	template<typename TAreaAffection>
	struct Logic final
	{
	private:
		Logic() = default;
	public:
		using instance = TAreaAffection;
		static_assert(IsInstance<instance>, "TAreaAffection must qualify to IsInstance concept.");

		using data_entry = typename instance::data_entry;
		static_assert(IsDataEntry<data_entry>, "TAreaAffection::data_entry must qualify to IsDataEntry concept.");

		static Logic<instance> Instance;

		/*!
		* @brief For special use-case in PerCellProcess for FootClass, BulletClass
		*/
		void InOut(const data_entry& entry, short radius, int radiusSq
			, __CellExt_ExtData* pCurrentExt
			, __CellExt_ExtData* pPreviousExt
		);
		void In(const data_entry& entry, short radius, int radiusSq, __CellExt_ExtData* pExt);
		void Out(const data_entry& entry, short radius, int radiusSq, __CellExt_ExtData* pExt);
		void ClearInstance(instance* pInst);
		void ClearEntry(const data_entry& entry);
	};

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void MaxRanges(short& radius, int& radiusSq
		, const typename TDataEntries&... entries
	);

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void In(int radius, int radiusSq
		, __CellExt_ExtData* pExt
		, typename TDataEntries&... entries
	);

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void Out(int radius, int radiusSq
		, __CellExt_ExtData* pExt
		, typename TDataEntries&... entries
	);

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void InOut(int radius, int radiusSq
		, __CellExt_ExtData* pCurrent, __CellExt_ExtData* pPrevious
		, typename TDataEntries&... entries
	);	
}
