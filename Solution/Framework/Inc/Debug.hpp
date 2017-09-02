/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "../Inc/Logger.hpp"

#if defined NDEBUG
constexpr bool IS_DEBUG = false;
#else
constexpr bool IS_DEBUG = true;
#endif

/* Writes information to logger.
*/
template <typename ...TArgs>
void LOG_INFO( TArgs&& ...args );
/* Writes warning to logger.
*/
template <typename ...TArgs>
void LOG_WARN( TArgs&& ...args );
/* Writes error to logger.
*/
template <typename ...TArgs>
void LOG_ERROR( TArgs&& ...args );

/* Writes information to logger, but only in DEBUG mode.
*/
template <typename ...TArgs>
void LOG_INFO_D( TArgs&& ...args );
/* Writes warning to logger, but only in DEBUG mode.
*/
template <typename ...TArgs>
void LOG_WARN_D( TArgs&& ...args );
/* Writes error to logger, but only in DEBUG mode.
*/
template <typename ...TArgs>
void LOG_ERROR_D( TArgs&& ...args );

#include "../Src/Debug.inl"