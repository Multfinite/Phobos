#pragma once

#include <AbstractClass.h>
#include <AbstractTypeClass.h>

template<typename TInstance /* Instance of mechanic. SensorClass, ShieldClass, etc ... */>
struct data_entry; /* { using instance_type = TInstance; }; */

template<typename TInstance>
struct data_entry_of;// { using type = data_entry<TInstance>; };

template<typename TInstance>
#if 1
struct entry;
#else
struct entry
{
	static_assert(false, "must be specialized.");

	using type = typename data_entry_of<TInstance>::type;
	/*!
	* @brief Use it if parent is known
	*/
	template<typename TExtension>
	inline static constexpr type& of(typename TExtension::ExtData& ext) noexcept { static_assert(false, "not specialized."); } /* <- must be direct access to specific field. */
	/*!
	* @brief Use it if parent is unknown
	*/
	inline static type* of(AbstractClass& abs) noexcept { static_assert(false, "not specialized."); }
	/*!
	* @brief Use it if parent is unknown
	*/
	inline static type* of(AbstractTypeClass& absType) noexcept { static_assert(false, "not specialized."); }
};
#endif

template<typename T, typename TExtension>
concept IsDataEntriedType = requires(typename TExtension::ExtData& ext, AbstractClass& abs, AbstractTypeClass& absType
	, typename data_entry<T>::type* deptr, typename data_entry<T>::type* deref)
{
	typename T::parent_type; /* <- to what am i attached?*/
	deref = typename entry<T>::template of<TExtension>(ext);
	deptr = typename entry<T>::of(abs);
	deptr = typename entry<T>::of(absType);
};
