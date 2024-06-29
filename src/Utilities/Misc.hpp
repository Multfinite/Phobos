#pragma once

#include <string>
#include <map>

namespace detail
{
	struct CaseInsensitiveComparator
	{
		struct nocase_compare
		{
			bool operator() (const unsigned char& c1, const unsigned char& c2) const
			{
				return tolower(c1) < tolower(c2);
			}
		};
		bool operator() (const std::string& s1, const std::string& s2) const
		{
			return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), nocase_compare());
		}
	};
}

template<typename T>
concept HasRadius = requires(T x) { x.Radius; };

template<typename T> requires HasRadius<T>
struct RadiusLess
{
	using type = std::remove_pointer_t<std::remove_reference_t<T>>;

	bool operator() (type const& lhs, type const& rhs) const
	{
		return lhs.Radius < rhs.Radius;
	}
	bool operator() (type const* lhs, type const* rhs) const
	{
		return lhs->Radius < rhs->Radius;
	}
};

template<typename T> requires HasRadius<T>
struct RadiusGreater
{
	using type = std::remove_pointer_t<std::remove_reference_t<T>>;

	bool operator() (type const& lhs, type const& rhs) const
	{
		return lhs.Radius > rhs.Radius;
	}
	bool operator() (type const* lhs, type const* rhs) const
	{
		return lhs->Radius > rhs->Radius;
	}
};

#define GETTER_NAME(name) get_##name
#define SETTER_NAME(name) set_##name

#define GETTER_DECL(name, type) type GETTER_NAME(name)()
#define SETTER_DECL(name, type) void SETTER_NAME(name)(type value)

#define GETTER_V(name, field) std::remove_reference_t<decltype(field)> GETTER_NAME(name)()
#define GETTER_R(name, field) std::remove_reference_t<decltype(field)>& GETTER_NAME(name)()
#define GETTER_RC(name, field) std::remove_reference_t<decltype(field)> const& GETTER_NAME(name)()

#define SETTER_V(name, field) void SETTER_NAME(name)(std::remove_reference_t<decltype(field)> value)
#define SETTER_R(name, field) void SETTER_NAME(name)(std::remove_reference_t<decltype(field)>& value)
#define SETTER_RC(name, field) void SETTER_NAME(name)(std::remove_reference_t<decltype(field)> const& value)

#define GETTER_V_DEFAULT(name, field) GETTER_V(name, field) const { return field; }
#define GETTER_R_DEFAULT(name, field) GETTER_R(name, field) const { return field; }
#define GETTER_RC_DEFAULT(name, field) GETTER_RC(name, field) const { return field; }

#define SETTER_V_DEFAULT(name, field) SETTER_V(name, field) { field = value; }
#define SETTER_R_DEFAULT(name, field) SETTER_R(name, field) { field = value; }
#define SETTER_RC_DEFAULT(name, field) SETTER_RC(name, field) { field = value; }

#define GETSET_V(name, field) \
GETTER_V(name, field); \
SETTER_V(name, field); \

#define GETSET_ABS_V(name, field) \
virtual GETTER_V(name, field) = 0; \
virtual SETTER_V(name, field) = 0; \

#define GETSET_R(name, field) \
GETTER_R(name, field); \
SETTER_R(name, field); \

#define GETSET_ABS_R(name, field) \
virtual GETTER_R(name, field) = 0; \
virtual SETTER_R(name, field) = 0; \

#define GETSET_RC(name, field) \
GETTER_RC(name, field); \
SETTER_RC(name, field); \

#define GETSET_ABS_RC(name, field) \
virtual GETTER_RC(name, field) = 0; \
virtual SETTER_RC(name, field) = 0; \
