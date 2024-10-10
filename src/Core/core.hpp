#pragma once
#include <string>
#include <map>
#include <Phobos.h>

/*!
* @author Multfinite
* @brief It is just for cases when you need mixup different extensions for example, in a list.
*/
struct IExtension
{
	void* const Base;
protected:
	constexpr IExtension(void* base) noexcept : Base(base) { }
};

/*!
* @author Multfinite
* @brief Extension of basic game class. Stores data, virtual functions.
* @brief Extension hierarchy must be the same as basic game classes does.
* @brief It is replacement of old *Ext::ExtData classes. You must specialize this.
* @param TBase  basic game class to extend
*/
template<typename TBase>
class Extension;

/*!
* @author Multfinite
* @brief Pseudoclass which must inherited from a TBase.
* @brief It is replacement of old *Ext classes. You must specialize this.
* @brief NOTICE: ONLY GENERIC FUNCTIONS ALLOWED. Virtual functions, member fields are disallowed
* @brief NOTICE: sizeof(Proxt<TBase>) must be the same as sizeof(TBase)
* @param TBase basic game class to extend
*/
template<typename TBase>
struct Proxy;

template<typename TBase>
struct FormatterBase
{
	using base_type = typename TBase;
	using extension_type = typename Extension<base_type>;
	using base_type_ptr = base_type*;
	using const_base_type_ptr = const base_type*;
	using extension_type_ptr = extension_type*;

	base_type* SavingObject;
	IStream* SavingStream;
protected:
	constexpr FormatterBase() : SavingObject(nullptr), SavingStream(nullptr) { }
};

/*!
* @author Multfinite (reworked Container Container.h)
* @brief Common formatting interface basics for 
* @brief 
*/
template<typename TBase>
struct SelfContainedFormatterBase
{

};

/*!
* @author Multfinite
* @brief Serialization, deserialization, parsing are detached from Extension<TBase> and Proxy<TBase>
* @brief Formatter provides all these functions and metadata for it.
*/
template<typename TBase>
struct Formatter;
