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

class __CellExt_ExtData;

/*!
* @brief All logic for cell radius affection stored here.
* @brief File structure are:
* @author Multfinite
*/
namespace AreaAffection
{
	template<typename TAreaAffection> struct Logic;
	struct InstanceEntry;
	struct CellEntry;
	struct IInstance;

	void InitializeOnCell(IInstance* pInst, CellClass* cell);

	template<typename T>
	concept IsDataEntry = requires(T x, T * ptr, AbstractClass* abs
		, typename T::instance * pInst, short radius, typename T::instance::type * pType
		, HouseClass * pOwner
	) {
		typename T::instance;
		typename T::instance_ptr;
		typename T::instance::type;
		x.Items; // ValueableSet (based on std::set) which is sorted in descending order
		x.Items.empty(); x.Items.begin(); x.Items.end();
		abs = x.Parent;
		x = T(abs);
		pInst = x.GetMostRanged();
	};

	template<typename T>
	concept IsInstance = requires(T x
		, AbstractClass * abs, HouseClass * house
		, short radius, int radiusSq
		, CellClass * affectedCell
		, __CellExt_ExtData & cell
		, typename T::data_entry * de
		, T * ptr, bool b, CoordStruct coords, HouseClass * pOwner
		, typename T::type * pType
		, bool bool__
	) {
		T::Array; T::Array.empty(); T::Array.begin(); T::Array.end();
		b = x.ClearedByEntry;
		x.remove_from_array();

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
	* @brief It is generic way to store area affection data on different extension types.
	* @brief All data entries stored in `AreaAffection::InstanceEntry` struct which is must be the field of extension as `AreaAffection::InstanceEntry* const AreaAffection`.
	* @author Multfinite
	*/
	template<typename TInstance>
	struct DataEntry
	{
		using instance = TInstance;
		using instance_ptr = std::unique_ptr<instance>;
		using data_entry = DataEntry<instance>;

		static_assert(IsInstance<TInstance>, "Not area affection!");

		/*!
		* @brief Owning instance
		* @brief Currently supported: TechnoClass, BulletClass (projectile), CellClass
		*/
		Valueable<AbstractClass*> Parent;

		/*!
		* @brief Instances, owned by this.
		* @brief This means, that this should invoke In() and Out() functions.
		*/
		std::list<instance_ptr> Items;
		/*!
		* @brief Sorting is necessary for process functions.
		* @brief It will pass proceed of objects which radius is less then distance from center to current processing cell.
		*/
		std::set<instance*, typename instance::radius_less> SortedItems;
		/*!
		* @brief Flag to control destruction. TRUE means that this data entry was cleared by `Logic<TInstance>::ClearEntry`.
		*/
		bool ClearedByEntry = false;

		DataEntry(AbstractClass* pParent) : Parent(pParent) { }

		instance* GetMostRanged() const
		{
			return *SortedItems.begin(); // std::set is sorted
		}

		virtual void __on_instantiate(instance* pInst)
		{
			SortedItems.insert(pInst);
		}

		virtual void __on_deinstantiate(instance* pInst)
		{
			SortedItems.erase(pInst);
		}

		instance* Instantiate(typename instance::type* pType, HouseClass* pHouse, short radius)
		{
			instance_ptr& inst = Items.emplace_back(std::make_unique<instance>(pType, Parent, pHouse, radius));

			__on_instantiate(inst.get());

			if (auto* cell = abstract_cast<CellClass*>(Parent))
				InitializeOnCell(inst.get(), cell);
			return inst.get();
		}

		bool Deinstantiate(instance* pInst)
		{
			auto it = std::find_if(Items.begin(), Items.end(), [&pInst](instance_ptr const& x) { return x.get() == pInst; });
			if (it == Items.end())
				return false;

			__on_deinstantiate(pInst);

			Items.erase(it);
			return true;
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
				// TODO
				//.Process(this->Items)
				.Success();
		}
	};

	/*!
	* @author Multfinite
	* @brief Interface (with generic implementation lol) for any area affection instance.
	* @brief It links area affection type and it's owner.
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
		* @brief This flag used for desturction.
		* @brief Data entry can be destoryed or by data entry (with all owned instance) or individually.
		*/
		bool ClearedByEntry = false;

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
		* @brief MUST remove this from all associated static arrays.
		* @brief Should be redefined for each new type with internal Array.
		*/
		virtual void remove_from_array() { Array.remove(this); }

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
		 * @brief IT SHOULD NOT CHANGE `AffectedCell` OR INTERACT WITH IT.
		 * @note To understand what happens here see `VanillaSensorClass`
		 */
		virtual void In(__CellExt_ExtData& cell, short radius, int radiusSq) = 0;
		/*!
		 * @brief Unaffects given cell. This should remove generated cache of `IInstance::In`.
		 * @brief IT SHOULD NOT CHANGE `AffectedCell` OR INTERACT WITH IT.
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

	template<typename TAreaAffection>
	struct data_entry_of
	{
		using type = DataEntry<TAreaAffection>;
	};

	template<typename TAreaAffection>
	using data_entry_of_t = typename data_entry_of<TAreaAffection>::type;

	/*!
	* @brief Use it if parent is known
	*/
	template<typename TAreaAffection, typename TExtension>
	struct Entry
	{
		using type = data_entry_of_t<TAreaAffection>;
		inline static type& Of(typename TExtension::ExtData* pExt);
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

		using data_entry = data_entry_of_t<instance>;
		static_assert(IsDataEntry<data_entry>, "TAreaAffection::data_entry must qualify to IsDataEntry concept.");

		static Logic<instance> Instance;

		/*!
		* @brief For special use-case in PerCellProcess for FootClass. This should be called on every place where object is changing position.
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
	void In(short radius, int radiusSq
		, __CellExt_ExtData* pExt
		, typename TDataEntries&... entries
	);

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void Out(short radius, int radiusSq
		, __CellExt_ExtData* pExt
		, typename TDataEntries&... entries
	);

	template<typename ...TDataEntries>
		requires (IsDataEntry<TDataEntries> && ...)
	void InOut(short radius, int radiusSq
		, __CellExt_ExtData* pCurrent, __CellExt_ExtData* pPrevious
		, typename TDataEntries&... entries
	);
}
