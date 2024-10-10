#pragma once
#include "core.hpp"

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
	using formatter_type = Formatter<TValue>;

	member_type const Member;
	char const Key[];

	template<typename TString>
	constexpr entry_data(member_type member, TString propertyKey) :
		Member(member), Key(propertyKey)
	{}

	inline constexpr value_type value_of(base_type& object) const noexcept { object.*Member; }

	constexpr void parse(base_type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key)
	{
		std::string const key_ = sizeof(Key) > 0 ? (key + "." + std::string(Key)) : std::string(Key);
		formatter_type::parse(base.*Member, ini, parser, section, key_);
	}
	constexpr void serialize(base_type const& base, std::ostream& stream)
	{
		formatter_type::serialize(base.*Member, stream);
	}
	constexpr void deserialize(base_type& base, std::istream& stream)
	{
		formatter_type::deserialize(base.*Member, stream);
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

	constexpr void parse(base_type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key)
	{
		Data.parse(base, ini, parser, section, key);
	}
	constexpr void serialize(base_type const& base, std::ostream& stream)
	{
		Data.serialize(base, stream);
	}
	constexpr void deserialize(base_type& base, std::istream& stream)
	{
		Data.deserialize(base, stream);
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

	constexpr void parse(base_type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key)
	{			
		Data.parse(base, ini, parser, section, key);
		Next.parse(base, ini, parser, section, key);
	}
	constexpr void serialize(base_type const& base, std::ostream& stream)
	{
		Data.serialize(base, stream);
		Next.serialize(base, stream);
	}
	constexpr void deserialize(base_type& base, std::istream& stream)
	{
		Data.deserialize(base, stream);
		Next.deserialize(base, stream);
	}
};

template<typename TBase>
struct void_entry
{
	using base_type = TBase;

	constexpr void parse(base_type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key) {}
	constexpr void serialize(base_type const& base, std::ostream& stream){}
	constexpr void deserialize(base_type& base, std::istream& stream){}
};

template<typename TBase>
struct chain
{
	using base_type = TBase;
	using entry_type = void_entry<base_type>;

	entry_type Entry;

	template<typename ...T>
	constexpr chain(T&&... other) {}
	constexpr chain() {}
};

template<typename TBase, typename ...T>
struct chain
{
	using base_type = TBase;
	using entry_type = entry<base_type, T...>;

	entry_type Entry;

	constexpr chain(T&&... other) : Entry(other...) {}
};

template<typename TBase>
constexpr auto make_chain(TBase* _) noexcept
{
	return chain<std::remove_pointer_t<decltype(_)>>();
}

template<typename TBase, typename ...T>
constexpr auto make_chain(TBase* _, T&&... other) noexcept
{
	return chain<std::remove_pointer_t<decltype(_)>, T...>(other);
}

#define __FORMATTER_BODY_GENERIC(type) \
	static constexpr void parse(type& base, CCINIClass& ini, INI_EX& parser, std::string const& section, std::string const& key) { chain().Entry.parse(base, ini, parser, section, key); } \
	static constexpr void serialize(std::ostream& s, type const& o) { chain().Entry.serialize(o, s); } \
	static constexpr void deserialize(std::istream& s, type& o) { chain().Entry.deserialize(o, s); } \


#define __concat(a, b) a##b
#define __stringify(x) #x
#define __EXTENSION_GENERIC_FORMATTING(BaseClass) \
/*static_assert(IsFormatter<Formatter<BaseClass>>, __stringify(Formatter is incomplete of Extension<##BaseClass##>!));*/ \
std::ostream& operator<<(std::ostream& s, Extension<BaseClass> const& o) \
{ \
	Formatter<Extension<BaseClass>>::serialize(s, o); \
	return s; \
} \
std::istream& operator>>(std::istream& s, Extension<BaseClass>& o) \
{ \
	Formatter<Extension<BaseClass>>::deserialize(s, o); \
	return s; \
} \

#undef __stringify
#undef __concat
