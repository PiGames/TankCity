/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "PCH.hpp"

#include <initializer_list>

namespace con
{

/* Applies lambda 'F&& f' to every argument.
*/
template <typename F, typename ...TArgs>
inline constexpr void forEachArgument( F&& f, TArgs&&... args )
{
	// TODO: Change to fold expression: https://youtu.be/AqDsso3S5fg
	(void)std::initializer_list<int32>{( f( std::forward<TArgs>( args ) ), 0 )...};
}

/* Returns true if given value T is not equal to any of arguments.
*/
template <typename T, typename ...TArgs>
inline constexpr bool itIsNot( const T& valueToCheck, TArgs&& ...args )
{
	bool valToReturn = true;
	forEachArgument(
		[&]( const auto& arg ) {

		if ( valueToCheck == arg )
			valToReturn = false;
	}, std::forward<TArgs>( args )... );

	return valToReturn;
}

// ::value = true if parameter pack contais given type.
template <typename...>
struct is_one_of
{
	static constexpr bool value = false;
};

// ::value = true if parameter pack contais given type.
template <typename F, typename S, typename... T>
struct is_one_of<F, S, T...>
{
	static constexpr bool value =
		std::is_same<F, S>::value || is_one_of<F, T...>::value;
};

template <typename F, typename S, typename... T>
static constexpr bool is_one_of_v = is_one_of<F, S, T...>::value;

/* Returns true if given value T is equal to any of arguments.
*/
template <typename T, typename ...TArgs>
inline constexpr bool itIs( const T& valueToCheck, TArgs&& ...args )
{
	return !itIsNot( valueToCheck, std::forward<TArgs>( args )... );
}

struct consume_args final
{
	template <typename ...TArgs> consume_args( const TArgs&... ) {}
};

/* Loops over all variadic template types.
	Usage:
	auto lambda = [](auto& t) {};
	using lambda_t = decltype(lambda);
	forEachTemplateType<lambda_t, TArgs...>(std::forward<lambda_t>(lambda));
*/
template <typename F, typename T0, typename ...TArgs>
inline constexpr void forEachTemplateType( F&& f )
{
	f( T0() );

	if constexpr ( sizeof...( TArgs ) > 0 )
		forEachTemplateType<F, TArgs...>( std::forward<F>( f ) );
}
}