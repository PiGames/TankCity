/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

namespace con
{
// Forward declarations to avoid cross include.
class Time;
class Logger;
class Messenger;

/* Contains pointers to instances of objects that are only one per Application.
	References stay valid all time - they are pointing to instances of Game class.
*/
struct Context final
{
	static Time* time;
	static Logger* logger;
	static Messenger* messenger;
};

Time& gTime();
Logger& gLogger();
Messenger& gMessenger();
}