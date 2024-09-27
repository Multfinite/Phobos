#pragma once
#include "core.hpp"

#include <Utilities/INIParser.h>

#include <type_traits>
#include <concepts>

namespace Formatter
{
	/*!
	* @author Multfinite
	* @brief Metadata (traits) for parsing.
	* @brief Type parsing traits detached from extensions and other types.
	*/
	template<typename T>
	struct Metadata;

	/*!
	* @author Multfinite
	* @brief Interface for something that can be parsed from text file.
	* @brief Now supports only INI files, but TODO: make parse(...) for JSON.
	*/
	struct IParseable
	{
		/*!
		* @brief Parses data which object state-independent (invariant data). Any reference solving disallowed here.
		* @brief If something external can refer to own data of this object then all data must be initialized here (even instance created if nedeed).
		*/
		virtual void pre_parse(CCINIClass& ini, INI_EX& parser, std::string const& prefix) = 0;
		/*!
		* @brief Parses data which object state-dependent or need for lookup any other data.
		* @brief At this stage all object are exist and can be referensed by other objects. Reference solving should be placed here.
		*/
		virtual void post_parse(CCINIClass& ini, INI_EX& parser, std::string const& prefix) = 0;
		/*!
		* @briaf All object at this stage must be constructed already. Use to solve thing which can not be solvet at post_parse(...).
		*/
		virtual void post_init(CCINIClass& ini, INI_EX& parser, std::string const& prefix) = 0;
	};

	/*!
	* @author Multfinite
	* @brief Provides simple compile-time interface for autogenerting parser method.
	* @param TValue must be member pointer to field, can be obtained as &T::field and it is value type specialization;
	*/
	template<typename TMember, typename TBase, typename TValue>
	struct entry_data
	{
		using base_type = TBase;
		using value_type = TValue;
		using member_type = TMember;

		member_type const Member;
		char const Key[];

		template<typename TString>
		constexpr entry_data(member_type member, TString propertyKey) :
			Member(member), Key(propertyKey)
		{ }

		inline constexpr value_type value_of(base_type& object) const noexcept { object.*Member; }

		constexpr void parse(base_type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& prefix)
		{
			std::string const prefix_ = sizeof(Key) > 0 ? (prefix + "." + std::string(Key)) : std::string(Key);
			Formatter::parse(base.*Member, ini, parser, section, prefix_);
			return base;
		}
		constexpr void const& serialize(base_type const& base, std::ostream& stream)
		{
			Formatter::serialize(base.*Member, stream);
			return base;
		}
		constexpr void deserialize(base_type& base, std::istream& stream)
		{
			Formatter::deserialize(base.*Member, stream);
			return base;
		}
	};

	template<typename TBase, typename TMember, typename ...T>
	struct entry
	{
		using base_type = TBase;
		using member_type = TMember;
		using value_type = decltype(static_cast<TBase*>(nullptr)->*(static_cast<member_type>(nullptr)));

		using entry_type = entry_data<member_type, base_type, value_type>;
		using next_entry_type = entry<T...>;

		entry_type Data;
		next_entry_type Next;

		template<typename TString>
		constexpr entry(member_type member, TString propertyKey, T&&... other) :
			  Data(member, propertyKey)
			, Next(other...)
		{}

		constexpr void parse(base_type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& prefix)
		{			
			Data.parse(base, ini, parser, section, prefix);
			Next.parse(base, ini, parser, section, prefix);
			return base;
		}
		constexpr void serialize(base_type const& base, std::ostream& stream)
		{
			Data.serialize(base, stream);
			Next.serialize(base, stream);
			return base;
		}
		constexpr void deserialize(base_type& base, std::istream& stream)
		{
			Data.deserialize(base, stream);
			Next.deserialize(base, stream);
			return base;
		}
	};

	template<typename TBase, typename TMember>
	struct entry
	{
		using base_type = TBase;
		using member_type = TMember;
		using value_type = decltype(static_cast<TBase*>(nullptr)->*(static_cast<member_type>(nullptr)));

		using entry_type = entry_data<member_type, base_type, value_type>;

		entry_type Data;

		template<typename TString>
		constexpr entry(member_type member, TString propertyKey) :
			Data(member, propertyKey)
		{}

		constexpr void parse(base_type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& prefix)
		{
			Data.parse(base, ini, parser, section, prefix);
			return base;
		}
		constexpr void serialize(base_type const& base, std::ostream& stream)
		{
			Data.serialize(base, stream);
			return base;
		}
		constexpr void deserialize(base_type& base, std::istream& stream)
		{
			Data.deserialize(base, stream);
			return base;
		}
	};

	template<typename TBase, typename ...T>
	struct chain
	{
		using base_type = TBase;
		using entry_type = entry<base_type, T...>;

		entry_type Entry;

		constexpr chain(T&&... other) : Entry(other...)
		{ }
	};

	template<typename TBase, typename ...T>
	constexpr auto make_chain(TBase* _, T&&... other) noexcept
	{
		return chain<std::remove_pointer_t<decltype(_)>, T...>(other);
	}
};
