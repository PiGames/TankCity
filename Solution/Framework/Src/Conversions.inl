/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/Misc.hpp"
#include "../Inc/Types.hpp"

#include <sstream>
#include <cctype> // tolower

#pragma warning(push)
// Something about const arguments - it wants to TArgs&& be const!
#pragma warning(disable:26461)
// Warning about const char* passing (need for ToStr conversions)
#pragma warning(disable:26485)

namespace con
{
namespace priv
{
template <typename From>
inline auto ToStr( const From& src )
{
	if constexpr ( std::is_same_v<bool, From> )
		return src ? "true" : "false";
	else {
		if constexpr ( std::is_integral_v<From> )
			return std::to_string( +src );
		else if constexpr ( std::is_floating_point_v<From> )
			return std::to_string( src );
		else {
			std::stringstream out;
			out << src;
			return out.str();
		}
	}
}

template <typename From, typename ...TArgs>
inline auto ToStrVariadic( const From& src, TArgs&& ...rest )
{
	auto strToReturn = ToStr( src );
	forEachArgument( [&]( const auto& arg ) {
		strToReturn += ToStr( arg );
	}, std::forward<TArgs>( rest )... );

	return strToReturn;
}

inline std::string ToLower( std::string str )
{
	std::transform( str.begin(), str.end(), str.begin(), []( auto c ) {
		return To<char>( std::tolower( c ) );
	} );
	return str;
}

template <typename To_>
inline To_ FromStr( const std::string& src )
{
	if constexpr ( std::is_same_v<int8, To_> )
		return To<int8>( std::stoi( src ) );
	else if constexpr ( std::is_same_v<uint8, To_> )
		return To<uint8>( std::stoull( src ) );
	else if constexpr ( std::is_same_v<int16, To_> )
		return To<int16>( std::stoi( src ) );
	else if constexpr ( std::is_same_v<uint16, To_> )
		return To<uint16>( std::stoull( src ) );
	else if constexpr ( std::is_same_v<int32, To_> )
		return std::stoi( src );
	else if constexpr ( std::is_same_v<uint32, To_> )
		return To<uint32>( std::stoull( src ) );
	else if constexpr ( std::is_same_v<int64, To_> )
		return std::stoll( src );
	else if constexpr ( std::is_same_v<uint64, To_> )
		return std::stoull( src );
	else if constexpr ( std::is_same_v<float32, To_> )
		return std::stof( src );
	else if constexpr ( std::is_same_v<float64, To_> )
		return std::stod( src );
	else if constexpr ( std::is_same_v<bool, To_> )
		return !( ToLower( src ) == "false" || src == "0" );
	else
		static_assert( false, __FUNCTION__ "invalid from string conversion parameter" );
}
}

template <typename To_, typename From, typename ...TArgs>
inline To_ To( const From& src, TArgs&& ...args )
{
	if constexpr ( std::is_same_v<std::string, To_> )
	{
		if constexpr ( sizeof...( args ) > 0 )
			return priv::ToStrVariadic( src, std::forward<TArgs>( args )... );
		else
			return priv::ToStr( src );
	} else if constexpr ( std::is_same_v<std::string, From> )
		return priv::FromStr<To_>( std::string( src ) );
	else
		return static_cast<To_>( src );
}
}

#pragma warning(pop)