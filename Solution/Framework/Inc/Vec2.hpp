/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <algorithm>
#include <cmath>
// For fancy AsString method and ostream operators.
#include <sstream>

// Conversion to SFML type vector.
#include <SFML/System/Vector2.hpp>

#include "Conversions.hpp"
#include "Types.hpp"

namespace con
{
template <typename T>
struct Vec2;

template <typename T>
struct Vec2
{
	static const Vec2<T> ZERO;
	static const Vec2<T> ONE;
	static const Vec2<T> LEFT;
	static const Vec2<T> RIGHT;
	static const Vec2<T> UP;
	static const Vec2<T> DOWN;

	T x, y;

	Vec2();
	template <typename Y>
	Vec2( Y x_, Y y_ );
	template <typename Y>
	Vec2( const Vec2<Y>& second );
	template <typename Y>
	Vec2( const sf::Vector2<Y>& second );

	virtual ~Vec2() = default;

	template <typename Y>
	void Set( Y x_, Y y_ );
	template <typename Y>
	void Set( const Vec2<Y>& second );
	template <typename Y>
	void Set( const sf::Vector2<Y>& second );

	sf::Vector2<T> AsSFMLVec() const;
	std::string AsString() const;
	Vec2<T> Abs() const;
	T Min() const;
	T Max() const;

	T Length() const;
	T LengthSquared() const;
	template <typename Y>
	T DotProduct( const Vec2<Y>& second ) const;
	template <typename Y>
	T CrossProduct( const Vec2<Y>& second ) const;

	T Distance( const Vec2<T>& second );
	T DistanceSquared( const Vec2<T>& second );

	Vec2<T> operator-() const;

	template <typename Y>
	Vec2<T> operator+( const Vec2<Y>& second ) const;
	template <typename Y>
	Vec2<T> operator-( const Vec2<Y>& second ) const;
	template <typename Y>
	Vec2<T> operator*( const Vec2<Y>& second ) const;
	template <typename Y>
	Vec2<T> operator/( const Vec2<Y>& second ) const;

	template <typename Y>
	Vec2<T> operator+( Y value ) const;
	template <typename Y>
	Vec2<T> operator-( Y value ) const;
	template <typename Y>
	Vec2<T> operator*( Y value ) const;
	template <typename Y>
	Vec2<T> operator/( Y value ) const;

	template <typename Y>
	Vec2<T>& operator+=( const Vec2<Y>& second );
	template <typename Y>
	Vec2<T>& operator-=( const Vec2<Y>& second );
	template <typename Y>
	Vec2<T>& operator*=( const Vec2<Y>& second );
	template <typename Y>
	Vec2<T>& operator/=( const Vec2<Y>& second );

	template <typename Y>
	Vec2<T>& operator+=( Y value );
	template <typename Y>
	Vec2<T>& operator-=( Y value );
	template <typename Y>
	Vec2<T>& operator*=( Y value );
	template <typename Y>
	Vec2<T>& operator/=( Y value );

	template <typename Y>
	bool operator==( const Vec2<Y>& second ) const;
	template <typename Y>
	bool operator!=( const Vec2<Y>& second ) const;
	template <typename Y>
	bool operator<( const Vec2<Y>& second ) const;
	template <typename Y>
	bool operator>( const Vec2<Y>& second ) const;
	template <typename Y>
	bool operator<=( const Vec2<Y>& second ) const;
	template <typename Y>
	bool operator>=( const Vec2<Y>& second ) const;

	template <typename Y>
	bool operator==( Y value ) const;
	template <typename Y>
	bool operator!=( Y value ) const;
	template <typename Y>
	bool operator<( Y value ) const;
	template <typename Y>
	bool operator>( Y value ) const;
	template <typename Y>
	bool operator<=( Y value ) const;
	template <typename Y>
	bool operator>=( Y value ) const;
};

template <typename T>
const Vec2<T> Vec2<T>::ZERO = Vec2<T>();
template <typename T>
const Vec2<T> Vec2<T>::ONE = Vec2<T>( 1, 1 );
template <typename T>
const Vec2<T> Vec2<T>::LEFT = Vec2<T>( -1, 0 );
template <typename T>
const Vec2<T> Vec2<T>::RIGHT = Vec2<T>( 1, 0 );
template <typename T>
const Vec2<T> Vec2<T>::UP = Vec2<T>( 0, -1 );
template <typename T>
const Vec2<T> Vec2<T>::DOWN = Vec2<T>( 0, 1 );

template <typename T>
Vec2<T> operator+( T left, const Vec2<T>& right );
template <typename T>
Vec2<T> operator-( T left, const Vec2<T>& right );
template <typename T>
Vec2<T> operator*( T left, const Vec2<T>& right );
template <typename T>
Vec2<T> operator/( T left, const Vec2<T>& right );

template <typename T>
std::ostream& operator<<( std::ostream& os, const Vec2<T>& vec );

using Vec2f = Vec2<float32>;
using Vec2i = Vec2<int32>;
using Vec2u = Vec2<uint32>;

using point = Vec2f;
}

#include "../Src/Vec2.inl"