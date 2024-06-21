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
