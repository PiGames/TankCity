/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Guideline.hpp"
#include "../Inc/Debug.hpp"

#include <intrin.h> // __debugbreak

namespace con::priv
{
bool Failer::Failed() const
{
	return !this->condition;
}
bool Failer::NotFailed() const
{
	return this->condition;
}

Failer FuncExpects( bool cond, const char* condStr, const char* file, uint32 line )
{
	if ( !( !!( cond ) ) ) {
		if constexpr (IS_DEBUG)
			__debugbreak();

		LOG_ERROR( "Precondition ", condStr, " failure at ", file, ": ", line );
	}

	return { cond };
}
Failer FuncEnsures( bool cond, const char* condStr, const char* file, uint32 line )
{
	if ( !( !!( cond ) ) ) {
		if constexpr (IS_DEBUG)
			__debugbreak();

		LOG_ERROR( "Postcondition ", condStr, " failure at ", file, ": ", line );
	}

	return { cond };
}
}