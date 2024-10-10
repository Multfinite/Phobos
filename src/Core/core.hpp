#pragma once
#include <string>
#include <map>
#include <Phobos.h>
#include <Utilities/INIParser.h>

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

/*!
* @author Multfinite
* @brief Serialization, deserialization, parsing are detached from Extension<TBase> and Proxy<TBase>
* @brief Formatter provides all these functions and metadata for it.
*/
template<typename TBase>
struct Formatter;
