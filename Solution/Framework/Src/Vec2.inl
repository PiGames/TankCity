/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

namespace con
{
template <typename T>
inline Vec2<T>::Vec2() :
	x( T{} ), y( T{} )
{}

template <typename T>
template <typename Y>
inline Vec2<T>::Vec2( Y x_, Y y_ ) :
	x( std::move( To<T>( x_ ) ) ),
	y( std::move( To<T>( y_ ) ) )
{}

template <typename T>
template <typename Y>
inline Vec2<T>::Vec2( const Vec2<Y>& second ) :
	x( To<T>( second.x ) ),
	y( To<T>( second.y ) )
{}

template <typename T>
template <typename Y>
inline Vec2<T>::Vec2( const sf::Vector2<Y>& second ) :
	x( To<T>( second.x ) ),
	y( To<T>( second.y ) )
{}

template <typename T>
template <typename Y>
inline void Vec2<T>::Set( Y x_, Y y_ )
{
	this->x = std::move( To<T>( x_ ) );
	this->y = std::move( To<T>( y_ ) );
}

template <typename T>
template <typename Y>
inline void Vec2<T>::Set( const Vec2<Y>& second )
{
	*this = second;
}

template <typename T>
template <typename Y>
inline void Vec2<T>::Set( const sf::Vector2<Y>& second )
{
	this->Set( second.x, second.y );
}

template <typename T>
inline sf::Vector2<T> Vec2<T>::AsSFMLVec() const
{
	return { this->x, this->y };
}

template<typename T>
inline std::string Vec2<T>::AsString() const
{
	return To<std::string>( "Vec2( ", this->x, " | ", this->y, " )" );
}

template<typename T>
inline Vec2<T> Vec2<T>::Abs() const
{
	return Vec2<T>( To<T>( std::fabs( this->x ) ), To<T>( std::fabs( this->y ) ) );
}

template<typename T>
inline T Vec2<T>::Min() const
{
	return std::min( this->x, this->y );
}

template<typename T>
inline T Vec2<T>::Max() const
{
	return std::max( this->x, this->y );
}

template <typename T>
inline T Vec2<T>::Length() const
{
	// Calculate for nice precission, then cast if smaller is needed.
	return To<T>( std::sqrtf( this->x * this->x + this->y * this->y ) );
}

template <typename T>
inline T Vec2<T>::LengthSquared() const
{
	return this->x * this->x + this->y * this->y;
}

template<typename T>
inline T Vec2<T>::Distance( const Vec2<T>& second )
{
	return std::sqrt( this->DistanceSquared( second ) );
}

template<typename T>
inline T Vec2<T>::DistanceSquared( const Vec2<T>& second )
{
	return std::pow( second.x - this->x, 2 ) + std::pow( second.y - this->y, 2 );
}

template <typename T>
template <typename Y>
inline T Vec2<T>::DotProduct( const Vec2<Y>& second ) const
{
	return this->x * second.x + this->y * second.y;
}

template <typename T>
template <typename Y>
inline T Vec2<T>::CrossProduct( const Vec2<Y>& second ) const
{
	return this->x * second.x - this->y * second.y;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator-() const
{
	return Vec2<T>( -this->x, -this->y );
}

template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator+( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x + second.x, this->y + second.y );
}

template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator-( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x - second.x, this->y - second.y );
}

template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator*( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x * second.x, this->y * second.y );
}

template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator/( const Vec2<Y>& second ) const
{
	return Vec2<T>( this->x / second.x, this->y / second.y );
}


template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator+( Y value ) const
{
	return Vec2<T>( this->x + value, this->y + value );
}

template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator-( Y value ) const
{
	return Vec2<T>( this->x - value, this->y - value );
}

template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator*( Y value ) const
{
	return Vec2<T>( this->x * value, this->y * value );
}

template<typename T>
template<typename Y>
inline Vec2<T> Vec2<T>::operator/( Y value ) const
{
	return Vec2<T>( this->x / value, this->y / value );
}


template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator+=( const Vec2<Y>& second )
{
	this->x += To<T>( second.x ); this->y += To<T>( second.y );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator-=( const Vec2<Y>& second )
{
	this->x -= To<T>( second.x ); this->y -= To<T>( second.y );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator*=( const Vec2<Y>& second )
{
	this->x *= To<T>( second.x ); this->y *= To<T>( second.y );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator/=( const Vec2<Y>& second )
{
	this->x /= To<T>( second.x ); this->y /= To<T>( second.y );
	return *this;
}


template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator+=( Y value )
{
	this->x += To<T>( value ); this->y += To<T>( value );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator-=( Y value )
{
	this->x -= To<T>( value ); this->y -= To<T>( value );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator*=( Y value )
{
	this->x *= To<T>( value ); this->y *= To<T>( value );
	return *this;
}

template<typename T>
template<typename Y>
inline Vec2<T>& Vec2<T>::operator/=( Y value )
{
	this->x /= To<T>( value ); this->y /= To<T>( value );
	return *this;
}


template<typename T>
template<typename Y>
inline bool Vec2<T>::operator==( const Vec2<Y>& second ) const
{
	return this->x == To<T>( second.x ) && this->y == To<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator!=( const Vec2<Y>& second ) const
{
	return this->x != To<T>( second.x ) && this->y != To<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator<( const Vec2<Y>& second ) const
{
	return this->x < To<T>( second.x ) && this->y < To<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator>( const Vec2<Y>& second ) const
{
	return this->x > To<T>( second.x ) && this->y > To<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator<=( const Vec2<Y>& second ) const
{
	return this->x <= To<T>( second.x ) && this->y <= To<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator>=( const Vec2<Y>& second ) const
{
	return this->x >= To<T>( second.x ) && this->y >= To<T>( second.y );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator==( Y value ) const
{
	return this->x == To<T>( value ) && this->y == To<T>( value );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator!=( Y value ) const
{
	return this->x != To<T>( value ) && this->y != To<T>( value );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator<( Y value ) const
{
	return this->x < To<T>( value ) && this->y < To<T>( value );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator>( Y value ) const
{
	return this->x > To<T>( value ) && this->y > To<T>( value );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator<=( Y value ) const
{
	return this->x <= To<T>( value ) && this->y <= To<T>( value );
}

template<typename T>
template<typename Y>
inline bool Vec2<T>::operator>=( Y value ) const
{
	return this->x >= To<T>( value ) && this->y >= To<T>( value );
}


template<typename T>
inline Vec2<T> operator+( T left, const Vec2<T>& right )
{
	return right + left;
}

template<typename T>
inline Vec2<T> operator-( T left, const Vec2<T>& right )
{
	return right - left;
}

template<typename T>
inline Vec2<T> operator*( T left, const Vec2<T>& right )
{
	return right * left;
}

template<typename T>
inline Vec2<T> operator/( T left, const Vec2<T>& right )
{
	return right / left;
}

template<typename T>
std::ostream& operator<<( std::ostream& os, const Vec2<T>& vec )
{
	os << vec.AsString();
	return os;
}

}
