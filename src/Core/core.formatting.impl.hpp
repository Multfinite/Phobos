#pragma once
#include "core.hpp"

#include <Utilities/TemplateDef.h>

#include <optional>

/*
* Place here all specializations of
* - parse(...)
* - serialize(...)
* - deserialize(...)
*
* If will nedeed you can create core.formatting.impl.cpp
*/

#define PARSE_VALUE_DEFAULT(T) \
template<bool Allocate = true> \
void parse<T, Allocate>(T& data, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key) \
{ \
	detail::read<T, Allocate>(data, parser, section.c_str(), key.c_str()); \
} \
template<bool Allocate = true> \
void parse<std::optional<T>, Allocate>(std::optional<T>& data, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key) \
{ \
	if (parser.ReadString(section.c_str(), key.c_str())) \
	{ \
		const char* val = parser.value(); \
		\
		if (!_strcmpi(val, "<default>") || INIClass::IsBlank(val)) \
		{ \
			data.reset(); \
			return; \
		} \
		detail::read<T, Allocate>(*data, parser, pSection, pKey); \
		data = *data; \
	} \
} \

PARSE_VALUE_DEFAULT(uint8_t);
PARSE_VALUE_DEFAULT(uint16_t);
PARSE_VALUE_DEFAULT(uint32_t);
PARSE_VALUE_DEFAULT(uint64_t);

PARSE_VALUE_DEFAULT(int8_t);
PARSE_VALUE_DEFAULT(int16_t);
PARSE_VALUE_DEFAULT(int32_t);
PARSE_VALUE_DEFAULT(int64_t);

PARSE_VALUE_DEFAULT(bool);
PARSE_VALUE_DEFAULT(float);
PARSE_VALUE_DEFAULT(double);

PARSE_VALUE_DEFAULT(ArmorType);

PARSE_VALUE_DEFAULT(const char*);

#undef PARSE_INT_DEFAULT
