#pragma once

#include "Template.h"
#include "Constructs.h"
#include "Misc.hpp"

#include <SideClass.h>
#include <HouseTypeClass.h>

/*!
 * @brief This template is for something that varies depending on player house - country or/and faction. Faction has higher priority over side.
 */
template<typename T>
class Collaborable
{
public:
	Valueable<T> BaseValue {};
	ValueableMap<SideClass*, Nullable<T>> Sides;
	ValueableMap<HouseTypeClass*, Nullable<T>> Countries;

	Collaborable() = default;
	explicit Collaborable(T const& all) noexcept(noexcept(T { all })) : BaseValue { all } { }

	inline constexpr const T* GetEx(TechnoClass* pTechno) const noexcept { return &this->Get(pTechno); }
	inline constexpr const T* GetEx(SideClass* side) const noexcept
	{
		auto it = std::find(Sides.begin(), Sides.end(), side);
		if(it != Sides.end() && it->second.isset())
			return it->second.GetEx();
		return BaseValue.GetEx();
	}
	inline constexpr const T* GetEx(HouseTypeClass* house) const noexcept
	{
		auto it = std::find(Countries.begin(), Countries.end(), house);
		if(it != Countries.end() && it->second.isset())
			return it->second.GetEx();
		return GetEx(SideClass::Array->GetItem(house->SideIndex));
	}

	inline constexpr const T& Get(TechnoClass* pTechno) const noexcept { return *GetEx(pTechno); }
	inline constexpr const T& Get(SideClass* side) const noexcept { return *GetEx(side); }
	inline constexpr const T& Get(HouseTypeClass* house) const noexcept { return *GetEx(house); }

	/*!
	* @param pFlagFormat flag with stinhg placeholders, like "Warn.Eva%s%s". It will be transformed into "Warn.Eva" for basic, "Warn.Eva.Side.__side_name__" for each side and "Warn.Eva.Country.__country_name__" for each country
	*/
	inline void Read(INI_EX& parser, const char* pSection, const char* pFlagFormat)
	{
		BaseValue.Read(parser, pSection, string_format(pFlagFormat, "", "").c_str());
		for(SideClass* side : *SideClass::Array)
			Sides[side].Read(parser, pSection, string_format(pFlagFormat, ".Side.", side->Name).c_str());
		for(HouseTypeClass* country : *HouseTypeClass::Array)
			Countries[country].Read(parser, pSection, string_format(pFlagFormat, ".Country.", country->Name).c_str());
	}
	inline bool Load(PhobosStreamReader& Stm, bool RegisterForChange)
	{
		return Savegame::ReadPhobosStream(Stm, BaseValue, RegisterForChange)
			&&  Savegame::ReadPhobosStream(Stm, Sides, RegisterForChange)
			&&  Savegame::ReadPhobosStream(Stm, Countries, RegisterForChange);
	}
	inline bool Save(PhobosStreamWriter& Stm) const
	{
		return Savegame::WritePhobosStream(Stm, BaseValue)
			&& Savegame::WritePhobosStream(Stm, Sides)
			&& Savegame::WritePhobosStream(Stm, Countries);
	}
};

template<typename T>
class CollaborableIdx
{
public:
	ValueableIdx<T> BaseValue {};
	ValueableMap<SideClass*, NullableIdx<T>> Sides;
	ValueableMap<HouseTypeClass*, NullableIdx<T>> Countries;

	CollaborableIdx() = default;
	explicit CollaborableIdx(const int& all) noexcept(noexcept(int { all })) : BaseValue { all } { }

	inline constexpr const int* GetEx(TechnoClass* pTechno) const noexcept { return &this->Get(pTechno); }
	inline constexpr const int* GetEx(SideClass* side) const noexcept
	{
		auto it = std::find(Sides.begin(), Sides.end(), side);
		if (it != Sides.end() && it->second.isset())
			return it->second.GetEx();
		return BaseValue.GetEx();
	}
	inline constexpr const int* GetEx(HouseTypeClass* house) const noexcept
	{
		auto it = std::find(Countries.begin(), Countries.end(), house);
		if (it != Countries.end() && it->second.isset())
			return it->second.GetEx();
		return GetEx(SideClass::Array->GetItem(house->SideIndex));
	}

	inline constexpr const int& Get(TechnoClass* pTechno) const noexcept { return *GetEx(pTechno); }
	inline constexpr const int& Get(SideClass* side) const noexcept { return *GetEx(side); }
	inline constexpr const int& Get(HouseTypeClass* house) const noexcept { return *GetEx(house); }

	/*!
	* @param pFlagFormat flag with stinhg placeholders, like "Warn.Eva%s%s". It will be transformed into "Warn.Eva" for basic, "Warn.Eva.Side.__side_name__" for each side and "Warn.Eva.Country.__country_name__" for each country
	*/
	inline void Read(INI_EX& parser, const char* pSection, const char* pFlagFormat)
	{
		BaseValue.Read(parser, pSection, string_format(pFlagFormat, "", "").c_str());
		for (SideClass* side : *SideClass::Array)
			Sides[side].Read(parser, pSection, string_format(pFlagFormat, ".Side.", side->Name).c_str());
		for (HouseTypeClass* country : *HouseTypeClass::Array)
			Countries[country].Read(parser, pSection, string_format(pFlagFormat, ".Country.", country->Name).c_str());
	}
	inline bool Load(PhobosStreamReader& Stm, bool RegisterForChange)
	{
		return Savegame::ReadPhobosStream(Stm, BaseValue, RegisterForChange)
			&& Savegame::ReadPhobosStream(Stm, Sides, RegisterForChange)
			&& Savegame::ReadPhobosStream(Stm, Countries, RegisterForChange);
	}
	inline bool Save(PhobosStreamWriter& Stm) const
	{
		return Savegame::WritePhobosStream(Stm, BaseValue)
			&& Savegame::WritePhobosStream(Stm, Sides)
			&& Savegame::WritePhobosStream(Stm, Countries);
	}
};
