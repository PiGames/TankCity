/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>
#include <string>

#include "../../Framework/Inc/Time.hpp"
#include "../../Framework/Inc/Timer.hpp"
#include "../../Framework/Inc/Context.hpp"

int main()
{
	con::Timer timer;
	con::Time time;
	con::Context::time = &time;

	while ( true ) {
		con::gTime()._update();
		std::cout << con::gTime().Format( con::gTime().GetTimeMs() ) << '\r';
	}
	std::cin.get();
}