/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "PCH.hpp"
#include "Conversions.hpp"
#include "Guideline.hpp"
#include "Debug.hpp"

#include <random>

namespace con
{

/* Faster version of std::floor.
*/
template <typename T>
inline constexpr T fastFloor( float32 x )
{
	static_assert( std::is_integral_v<T>, "T must be integral" );
	union
	{
		float32 f;
		uint32 i;
	} val;
	val.f = x;
	int32 exponent = ( val.i >> 23 ) & 0xff; // extract the exponent field;
	int32 fractional_bits = 127 + 23 - exponent;
	if ( fractional_bits > 23 ) // abs(x) < 1.0
		return 0;
	if ( fractional_bits > 0 )
		val.i &= ~( ( 1U << fractional_bits ) - 1 );

	return To<T>( val.f );
}

namespace Random
{
namespace priv
{
static std::mt19937 rndEngine( To<uint32>( std::chrono::steady_clock::now().time_since_epoch().count() ) );
}
template <typename T, typename Y>
inline T value( T min, Y max )
{
	static_assert( std::is_integral_v<T> || std::is_floating_point_v<T> );
	T maxCasted = To<T>( max );

	if ( Expects( min < maxCasted ).Failed() ) {
		return min;
	}
	if ( Expects( min != maxCasted ).Failed() ) {
		return min;
	}

	if constexpr ( std::is_integral_v<T> )
	{
		std::uniform_int_distribution<T> dist( min, maxCasted );
		return dist( priv::rndEngine );
	} else if constexpr ( std::is_floating_point_v<T> )
	{
		std::uniform_real_distribution<T> dist( min, maxCasted );
		return dist( priv::rndEngine );
	}
}
}
}