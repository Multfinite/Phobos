#pragma once

#include <cstdint>
#include <type_traits>

/* Created by Multfinite for future use. */

template<typename T> struct extension_of
{
	/* define your extension here in specializations. */
	using type = void;
	static_assert(false, "extension_of generic used. Invalid type given or maybe forgot to specialize this for new extension? Also be sure that all necessary headers included.");
};
template<typename T> using extension_of_t = extension_of<T>::type;

enum struct Canary : uint32_t
{
	Invalid = 0
};

enum struct ExtOffset : uint32_t
{
	Invalid = 0
};

template<typename T> struct canary_of
{
	static constexpr Canary value = Canary::Invalid;
	static constexpr std::underlying_type_t<Canary> raw_value = static_cast<std::underlying_type_t<Canary>>(value);
	static_assert(false, "canary_of generic used. Invalid type given or maybe forgot to specialize this for new extension? Also be sure that all necessary headers included.");
};
template<typename T> using canary_of_v = canary_of<T>::value;
template<typename T> using canary_of_rw = canary_of<T>::raw_value;

template<typename T> struct ext_offset_of
{
	static constexpr Canary value = Canary::Invalid;
	static constexpr std::underlying_type_t<Canary> raw_value = static_cast<std::underlying_type_t<Canary>>(value);
	static_assert(false, "ext_offset_of generic used. Invalid type given or maybe forgot to specialize this for new extension? Also be sure that all necessary headers included.");
};
template<typename T> using ext_offset_of_v = ext_offset_of<T>::value;
template<typename T> using ext_offset_of_rw = ext_offset_of<T>::raw_value;
