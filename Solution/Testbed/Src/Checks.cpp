/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Guideline.hpp"
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

	if ( Expects( false ).Failed() )
		std::cout << "Expects failed (OK)\n";
	if ( Ensures( false ).Failed() )
		std::cout << "Ensures failed (OK)\n";
	if ( Expects( true ).Failed() )
		std::cout << "Expects failed (???)\n";
	if ( Ensures( true ).Failed() )
		std::cout << "Ensures failed (???)\n";

	std::unique_ptr<int> x;

	con::NotNull<int*> i( x.get() );

	x = std::make_unique<int>( 123 );
	con::NotNull<int*> y( x.get() );

	std::cin.get();
}