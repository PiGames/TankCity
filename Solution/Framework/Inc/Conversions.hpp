/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

namespace con
{
// Forward declaration for private functions.
template <typename To_, typename From, typename ...TArgs>
inline To_ To( const From& src, TArgs&& ...args );

namespace priv
{
template <typename From>
auto ToStr( const From& src );
template <typename From, typename ...TArgs>
auto ToStrVariadic( const From& src, TArgs&& ...rest );
inline std::string ToLower( std::string str );
template <typename To_>
inline To_ FromStr( const std::string& src );
}

/* Converts given types. Usage:
	To<std::string>(123.5);
	To<double>("678.9");
	To<std::string>("X = ", x, ".")
	Conversion to std::string is made by std::stringstream,
	so you must override operator<< and you're done.
*/
template <typename To_, typename From, typename ...TArgs>
inline To_ To( const From& src, TArgs&& ...args );
}

#include "../Src/Conversions.inl"