/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <chrono>

#include "Types.hpp"

/* Timer class based on Banshee Engine implemenation by Marko Pintera (marko.pintera@gmail.com).
	www.banshee3d.com
*/

namespace con
{
/* Measures time.
*/
class Timer final
{
public:
	Timer();

	/* Returns time in milliseconds since timer was initialized or last reset.
	*/
	uint64 GetMilliseconds() const;
	/* Returns time in microseconds since timer was initialized or last reset.
	*/
	uint64 GetMicroseconds() const;
	/* Returns the time at which the timer was initialized, in milliseconds.
	*/
	uint64 GetStartMs() const;

	/* Reset the timer to zero.
	*/
	void Reset();

private:
	std::chrono::high_resolution_clock clock;
	std::chrono::high_resolution_clock::time_point startTime;
};
}