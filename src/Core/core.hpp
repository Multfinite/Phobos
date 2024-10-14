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
* @brief Contains the chain of fields for processing. It should be used for formatting and parsing.
* @brief Formatter provides all these functions and metadata for it.
* @brief See make_chain(...) functions and its usage.
* @param T Any type that should be parsed in any case.
*/
template<typename T>
struct Formatter;

template<typename TFormatter>
concept IsFormatter = requires(
	  typename TFormatter::type& o
	, std::ostream& out
	, std::istream& in
	, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key
) {
	typename TFormatter::type;
	TFormatter::parse(o, ini, parser, section, key);
	TFormatter::serialize(out, o);
	TFormatter::deserialize(in, o);
};

#pragma region Formatting

#include <type_traits>
#include <concepts>
#include <Utilities/INIParser.h>



/*!
* @author Multfinite
* @brief Parse object from INI file at specific section with specific key
*/
template<typename T, bool Allocate = true>
void parse(T& data, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key);

/*!
* @author Mulfinite
* @brief Save object binary to stream
*/
template<typename T>
T const& serialize(T const& data, std::ostream& stream);

/*!
* @author Multfinite
* @brief Load object from binary stream
*/
template<typename T>
T& deserialize(T& data, std::istream& stream);

/*!
* @author Multfinite
* @brief Read objects of T as enumerable list
*/
template<typename T>
void read_types();



#pragma regionend
