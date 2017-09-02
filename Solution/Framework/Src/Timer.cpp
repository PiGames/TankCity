/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"

#include "../Inc/Timer.hpp"

using namespace std::chrono;

namespace con
{
Timer::Timer() :
	startTime( this->clock.now() )
{}

uint64 Timer::GetMilliseconds() const
{
	const auto newTime = this->clock.now();
	duration<float64> dur = newTime - this->startTime;

	return duration_cast<milliseconds>( dur ).count();
}

uint64 Timer::GetMicroseconds() const
{
	const auto newTime = this->clock.now();
	duration<float64> dur = newTime - this->startTime;

	return duration_cast<microseconds>( dur ).count();
}

uint64 Timer::GetStartMs() const
{
	const nanoseconds startTimeNs = this->startTime.time_since_epoch();

	return duration_cast<milliseconds>( startTimeNs ).count();
}

void Timer::Reset()
{
	this->startTime = this->clock.now();
}
}