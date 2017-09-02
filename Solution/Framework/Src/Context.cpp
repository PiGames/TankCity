/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"

#include "../Inc/Context.hpp"

#pragma warning(push)
// Assigning nullptr to static variable. Duh
#pragma warning(disable:26425)

namespace con
{
Time* Context::time = nullptr;
Logger* Context::logger = nullptr;
Messenger* Context::messenger = nullptr;

Time& gTime()
{
	return *Context::time;
}
Logger& gLogger()
{
	return *Context::logger;
}
Messenger& gMessenger()
{
	return *Context::messenger;
}
}

#pragma warning(pop)