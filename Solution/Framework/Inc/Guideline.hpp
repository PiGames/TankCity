/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

/*
	Based on: https://github.com/Microsoft/GSL/ NotNull is just copy from
	their repository.
*/

#include <sstream> // not_null ostream
#include "Types.hpp" // uint32

namespace con
{
namespace priv
{
class Failer final
{
public:
	Failer( bool condition_ ) :
		condition( condition_ )
	{}

	bool Failed() const;
	bool NotFailed() const;

private:
	bool condition;
};

Failer FuncExpects( bool cond, const char* condStr, const char* file, uint32 line );
Failer FuncEnsures( bool cond, const char* condStr, const char* file, uint32 line );
}
}

#define Expects( cond ) con::priv::FuncExpects( cond, #cond, __FILE__, __LINE__ )
#define Ensures( cond ) con::priv::FuncEnsures( cond, #cond, __FILE__, __LINE__ )

namespace con
{
//
// NotNull
//
// Restricts a pointer or smart pointer to only hold non-null values.
//
// Has zero size overhead over T.
//
// If T is a pointer (i.e. T == U*) then
// - allow construction from U*
// - disallow construction from nullptr_t
// - disallow default construction
// - ensure construction from null U* fails
// - allow implicit conversion to U*
//
template <class T>
class NotNull final
{
public:
	static_assert( std::is_assignable<T&, std::nullptr_t>::value, "T cannot be nullptr" );

	template <typename U, typename Dummy = std::enable_if_t<std::is_convertible<U, T>::value>>
	constexpr NotNull( U&& u ) : ptr_( std::forward<U>( u ) )
	{
		Expects( ptr_ != nullptr );
	}

	template <typename U, typename Dummy = std::enable_if_t<std::is_convertible<U, T>::value>>
	constexpr NotNull( const NotNull<U>& other ) : NotNull( other.get() )
	{}

	NotNull( const NotNull& other ) = default;
	NotNull& operator=( const NotNull& other ) = default;

	constexpr T get() const
	{
		Ensures( ptr_ != nullptr );
		return ptr_;
	}

	constexpr operator T() const { return get(); }
	constexpr T operator->() const { return get(); }
	constexpr auto operator*() const { return *get(); }

	// prevents compilation when someone attempts to assign a null pointer constant
	NotNull( std::nullptr_t ) = delete;
	NotNull& operator=( std::nullptr_t ) = delete;

	// unwanted operators...pointers only point to single objects!
	NotNull& operator++() = delete;
	NotNull& operator--() = delete;
	NotNull operator++( int ) = delete;
	NotNull operator--( int ) = delete;
	NotNull& operator+=( std::ptrdiff_t ) = delete;
	NotNull& operator-=( std::ptrdiff_t ) = delete;
	void operator[]( std::ptrdiff_t ) const = delete;

private:
	T ptr_;
};

template <class T>
std::ostream& operator<<( std::ostream& os, const NotNull<T>& val )
{
	os << val.get();
	return os;
}

template <class T, class U>
auto operator==( const NotNull<T>& lhs, const NotNull<U>& rhs )
{
	return lhs.get() == rhs.get();
}

template <class T, class U>
auto operator!=( const NotNull<T>& lhs, const NotNull<U>& rhs )
{
	return lhs.get() != rhs.get();
}

template <class T, class U>
auto operator<( const NotNull<T>& lhs, const NotNull<U>& rhs )
{
	return lhs.get() < rhs.get();
}

template <class T, class U>
auto operator<=( const NotNull<T>& lhs, const NotNull<U>& rhs )
{
	return lhs.get() <= rhs.get();
}

template <class T, class U>
auto operator>( const NotNull<T>& lhs, const NotNull<U>& rhs )
{
	return lhs.get() > rhs.get();
}

template <class T, class U>
auto operator>=( const NotNull<T>& lhs, const NotNull<U>& rhs )
{
	return lhs.get() >= rhs.get();
}

// more unwanted operators
template <class T, class U>
std::ptrdiff_t operator-( const NotNull<T>&, const NotNull<U>& ) = delete;
template <class T>
NotNull<T> operator-( const NotNull<T>&, std::ptrdiff_t ) = delete;
template <class T>
NotNull<T> operator+( const NotNull<T>&, std::ptrdiff_t ) = delete;
template <class T>
NotNull<T> operator+( std::ptrdiff_t, const NotNull<T>& ) = delete;

}