/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/
#pragma once

#include "PCH.hpp"

#include "Timer.hpp"
#include "Single.hpp"

/* Time class based on Banshee Engine implemenation by Marko Pintera (marko.pintera@gmail.com).
  www.banshee3d.com
*/

namespace con
{
/* Manages all time related functionality.
*/
class Time final :
	public Single<Time>
{
public:
	Time();

	/* Returns the time elapsed since application start, in seconds. Updated once per frame.
	*/
	float32 GetTime() const;
	/* Returns the time elapsed since application start, in milliseconds. Updated once per frame.
	*/
	uint64 GetTimeMs() const;
	/* Returns the precise time since application start, in microseconds. Unlike other time methods this is not only
	  updated every frame, but will return exact time at the moment it is called.
	*/
	uint64 GetTimePrecise() const;

	/* Returns the time since last frame was executed. Only gets updated once per frame.
	*/
	float32 GetFrameDelta() const;
	/* Returns the time at which the application was started, counting from system start.
	*/
	uint64 GetStartTimeMs() const;
	/* Returns time formated as:
	  HH:MM:SS
	  with leading zeroes.
	  ms - time as milliseconds.
	*/
	static std::string Format( uint64 ms );

	/* Called every frame. Should only be called by Application.
	*/
	void _update();

	/* Multiply with time in microseconds to get a time in seconds.
	*/
	static constexpr float64 MICROSEC_TO_SEC = 1.0 / 1'000'000.0;

private:
	Timer timer;

	float32 frameDelta;
	float32 timeSinceStart;
	uint64 timeSinceStartMs;

	uint64 appStartTime;
	uint64 lastFrameTime;
};
}
