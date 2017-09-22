/*
	Untitled_Guys 2017
*/

#include "Pawn.hpp"
#include "Context.hpp"
#include "Debug.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

using namespace con;

class TestController :
	public PawnController
{
	void Update() override
	{
		auto& pawn = *this->GetPawn();
		pawn.Move( ( Vec2f::DOWN + Vec2f::RIGHT ) * 0.1 );
		pawn.Rotate( 1.5f );
		LOG_INFO( "Deg: ", To<int16>(pawn.GetRotation()), " Pos: ", pawn.GetPosition() );
	}
};


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
	
	sf::RenderWindow window( {800,600}, "Pawn" );
	window.setFramerateLimit( 60 );
	sf::Event ev;
	Pawn testPawn;

	testPawn.DrawableRef().RectangleShape() = sf::RectangleShape( { 64,64 } );
	testPawn.DrawableRef().RectangleShape().setFillColor( sf::Color::Green );
	testPawn.ResetController<TestController>();

	while ( window.isOpen() ) {
		while ( window.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				window.close();
		}

		testPawn.Update();

		window.clear();
		testPawn.Draw( window );
		window.display();
	}
}