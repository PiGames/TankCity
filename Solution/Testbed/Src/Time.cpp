/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>
#include <string>

#include "Time.hpp"
#include "Timer.hpp"
#include "Context.hpp"

int main()
{
	con::Timer timer;
	con::Time time;
	con::Context::time = &time;

	while ( true ) {
		con::gTime()._update();
		std::cout << con::gTime().Format( con::gTime().SinceAppStartMs() ) << '\r';
	}
	std::cin.get();
}
