/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>

#include "../../Framework/Inc/Debug.hpp"

int main()
{
	// Need to initialize. This code will be somewhere in engine initialization.
	con::Logger logger;
	con::Time time;
	logger.SetConsoleOutputStream( &std::cout );
	con::Context::time = &time;
	con::Context::logger = &logger;

	LOG_INFO( "I'm information! No. ", 1, "." );
	LOG_WARN( "I'm warning! No. ", 2, "." );
	LOG_ERROR( "I'm error! No. ", 3, "." );

	LOG_INFO_D( "I'm information! No. ", 4, ". Shh, I'm DEBUG!" );
	LOG_WARN_D( "I'm warning! No. ", 5, ". Shh, I'm DEBUG!" );
	LOG_ERROR_D( "I'm error! No. ", 6, ". Shh, I'm DEBUG!" );

	std::cin.get();

	for ( con::uint8 i = 0; i < 255; i++ ) {
		con::Context::time->_update();
		LOG_INFO( "Value: ", +i );
	}

	std::cin.get();
}