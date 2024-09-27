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

namespace Formatter
{
	/*!
	* @author Multfinite
	* @brief For each data type (which can be field and should be parsed) must be defined specialization (even for primitive types).
	* @param T are data type
	* @param data - target variable (reference)
	* @param ini - INI file which currently parsing
	* @param parser - INI_EX for ini
	* @param prefix text that will be concatanated as prefix to key. It used for reference-like logic ("Shield.0" + keyname = real key)
	*/
	template<typename T, bool Allocate = true>
	void parse(T& data, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& prefix);

	template<typename T>
	T const& serialize(T const& data, std::ostream& stream);

	template<typename T>
	T& deserialize(T& data, std::istream& stream);
}
