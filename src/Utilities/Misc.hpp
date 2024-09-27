#pragma once

#include <string>
#include <map>
#include <unordered_map>

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

/* https://stackoverflow.com/a/38140932 */

inline void hash_combine(std::size_t& seed) { }

template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	hash_combine(seed, rest...);
}

#define MAKE_HASHABLE(type, ...) \
    namespace std {\
        template<> struct std::hash<type> {\
            std::size_t operator()(type const& t) const {\
                std::size_t ret = 0;\
                hash_combine(ret, __VA_ARGS__);\
                return ret;\
            }\
        };\
    }

/* https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf */
template<typename ... Args>
std::string string_format(std::string const& format, Args ... args)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
