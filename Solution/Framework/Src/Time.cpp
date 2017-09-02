/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"

#include "../Inc/Conversions.hpp"
#include "../Inc/Time.hpp"
#include "../Inc/Math.hpp"

namespace con
{
Time::Time() :
	frameDelta( 0.0f ), timeSinceStart( 0.0f ), timeSinceStartMs( 0 ),
	appStartTime( this->timer.GetStartMs() ),
	lastFrameTime( this->timer.GetMicroseconds() ),
	Single<Time>()
{}

float32 Time::GetTime() const
{
	return this->timeSinceStart;
}

uint64 Time::GetTimeMs() const
{
	return this->timeSinceStartMs;
}

uint64 Time::GetTimePrecise() const
{
	return this->timer.GetMicroseconds();
}

float32 Time::GetFrameDelta() const
{
	return this->frameDelta;
}

uint64 Time::GetStartTimeMs() const
{
	return this->appStartTime;
}

// From: https://stackoverflow.com/a/6313008/6696102
std::string Time::Format( uint64 ms )
{
	// No float division needed.
	const uint64 secNum = ms / 1'000;

	const auto hours = fastFloor<uint64>( secNum / 3600.0f );
	const auto minutes = fastFloor<uint64>( ( secNum - ( hours * 3600 ) ) / 60.0f );
	const auto seconds = secNum - ( hours * 3600 ) - ( minutes * 60 );

	std::string str( "" );

	if ( hours < 10 ) str += '0';
	str += To<std::string>( hours ) + ':';
	if ( minutes < 10 ) str += '0';
	str += To<std::string>( minutes ) + ':';
	if ( seconds < 10 ) str += '0';
	str += To<std::string>( seconds );

	return str;
}

void Time::_update()
{
	auto currentFrameTime = this->timer.GetMicroseconds();

	this->frameDelta = To<float32>( ( currentFrameTime - this->lastFrameTime ) * Time::MICROSEC_TO_SEC );
	this->timeSinceStartMs = To<uint64>( currentFrameTime / 1'000 );
	this->timeSinceStart = this->timeSinceStartMs / 1'000.0f;

	this->lastFrameTime = currentFrameTime;
}
}