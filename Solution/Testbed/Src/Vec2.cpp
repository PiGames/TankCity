/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Vec2.hpp"
#include "Debug.hpp"

#include <iostream>

using namespace con;
static void Init()
{
	static Time time;
	static Logger logger;
	logger.SetConsoleOutputStream( &std::cout );
	Context::time = &time;
	Context::logger = &logger;
}

int main()
{
	Init();

	Vec2f conVec2f;
	Vec2i conVec2i;

	conVec2f = { 1.5f,2.3f };
	conVec2i = { 3,-4 };

	LOG_INFO( "conVec2f: ", conVec2f );
	LOG_INFO( "conVec2i: ", conVec2i );

	LOG_INFO( "conVec2f Min: ", conVec2f.Min() );
	LOG_INFO( "conVec2i Min: ", conVec2i.Min() );

	LOG_INFO( "conVec2f Max: ", conVec2f.Max() );
	LOG_INFO( "conVec2i Max: ", conVec2i.Max() );

	LOG_INFO( "conVec2f Abs: ", conVec2f.Abs() );
	LOG_INFO( "conVec2i Abs: ", conVec2i.Abs() );

	LOG_INFO( "conVec2f Length: ", conVec2f.Length() );
	LOG_INFO( "conVec2i Length: ", conVec2i.Length() );

	LOG_INFO( "conVec2f LengthSquared: ", conVec2f.LengthSquared() );
	LOG_INFO( "conVec2i LengthSquared: ", conVec2i.LengthSquared() );

	LOG_INFO( "conVec2f DotProduct: ", conVec2f.DotProduct( conVec2i ) );
	LOG_INFO( "conVec2i DotProduct: ", conVec2i.DotProduct( conVec2f ) );

	LOG_INFO( "conVec2f CrossProduct: ", conVec2f.CrossProduct( conVec2i ) );
	LOG_INFO( "conVec2i CrossProudct: ", conVec2i.CrossProduct( conVec2f ) );

	LOG_INFO( "conVec2f Distance: ", conVec2f.Distance( conVec2i ) );
	LOG_INFO( "conVec2i Distance: ", conVec2i.Distance( conVec2f ) );

	LOG_INFO( "conVec2f DistanceSquared: ", conVec2f.DistanceSquared( conVec2i ) );
	LOG_INFO( "conVec2i DistanceSquared: ", conVec2i.DistanceSquared( conVec2f ) );

	LOG_INFO( "ZERO = ", Vec2i::ZERO );
	LOG_INFO( "ONE = ", Vec2i::ONE );
	LOG_INFO( "LEFT = ", Vec2i::LEFT );
	LOG_INFO( "RIGHT = ", Vec2i::RIGHT );
	LOG_INFO( "UP = ", Vec2i::UP );
	LOG_INFO( "DOWN = ", Vec2i::DOWN );

	std::cin.get();
}