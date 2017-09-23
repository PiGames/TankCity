/*
	Untitled_Guys 2017
*/

#include "Character.hpp"
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
		LOG_INFO( "Deg: ", To<int16>( pawn.GetRotation() ), " Pos: ", pawn.GetPosition() );
	}

	int32 GetID() const override
	{
		return 0;
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

	sf::RenderWindow window( { 800,600 }, "Character" );
	window.setFramerateLimit( 60 );
	sf::Event ev;
	Character characterA, characterB;

	characterA.DrawableRef().RectangleShape() = sf::RectangleShape( { 64,64 } );
	characterA.DrawableRef().RectangleShape().setFillColor( sf::Color::Green );
	characterA.ResetController<TestController>();
	characterB.DrawableRef() = characterA.DrawableRef();
	characterB.ResetController<TestController>();
	characterB.SetPosition( { 0, 300 - 32 } );

	while ( window.isOpen() ) {
		while ( window.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				window.close();
		}

		characterA.Update();
		characterB.Update();

		window.clear();
		characterA.Draw( window );
		characterB.Draw( window );
		window.display();
	}
}