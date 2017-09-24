/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Math.hpp"
#include "Debug.hpp"
#include <iostream>

static void Init()
{
	static con::Time time;
	static con::Logger logger;
	logger.SetConsoleOutputStream( &std::cout );
	con::Context::time = &time;
	con::Context::logger = &logger;
}

int main()
{
	Init();

	LOG_INFO( "Random int32<-64,64> = ", con::Random::value( -64, 64 ) );
	LOG_INFO( "Random int32<64,-64> = ", con::Random::value( 64, -64 ) );
	LOG_INFO( "Random float32<-0.64f, 0.64f> = ", con::Random::value( -0.64f, 0.64f ) );
	LOG_INFO( "Random float32<0.64f, -0.64f> = ", con::Random::value( 0.64f, -0.64f ) );
	LOG_INFO( "Random float32<-0.64f, 64> = ", con::Random::value( -0.64f, 64 ) );
	LOG_INFO( "Random int32<-64, 0.64f> = ", con::Random::value( -64, 0.64f ) );

	std::cin.get();
}