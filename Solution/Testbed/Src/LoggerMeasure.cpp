/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>
#include <fstream>

#include "Logger.hpp"
#include "Debug.hpp"

static void Init()
{
	static con::Time time;
	static con::Logger logger;
	logger.SetConsoleOutputStream( &std::cout );
	static std::ofstream file( "measure.txt" );
	logger.SetFileOutputStream( &file );
	
	con::Context::time = &time;
	con::Context::logger = &logger;

}
int main()
{
	std::ios::sync_with_stdio( false );
	Init();

	con::Timer timer;
	timer.Reset();
	for ( con::uint32 i = 0; i < 10'000; i++ )
		LOG_INFO( "i = ", i );

	LOG_INFO( "Result: ", timer.GetMilliseconds(), "ms" );

	std::cin.get();
}