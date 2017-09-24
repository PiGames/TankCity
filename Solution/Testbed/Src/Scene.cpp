/*
	Untitled_Guys 2017
*/

#include "Pawn.hpp"
#include "Scene.hpp"
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
		pawn.Move( ( Vec2f::DOWN + Vec2f::RIGHT ) * 0.3 );
		pawn.Rotate( 1.5f );
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

	sf::RenderWindow window( { 800,600 }, "Scene" );
	window.setFramerateLimit( 60 );
	sf::Event ev;

	Scene scene( 1 ); // should warn, given value smaller or equal to 1.

	auto& pawn1 = scene.Spawn<Pawn>();
	auto& pawn2 = scene.Spawn<Pawn>(); // should warn about resizing to value bigger than reserved
	pawn1.DrawableRef().RectangleShape() = sf::RectangleShape( { 64,64 } );
	pawn1.DrawableRef().RectangleShape().setFillColor( sf::Color::Green );
	pawn1.ResetController<TestController>();

	pawn2.ResetController<TestController>();
	pawn2.DrawableRef().CircleShape() = sf::CircleShape( 48, 8 );
	pawn2.DrawableRef().CircleShape().setFillColor( sf::Color::Red );

	pawn1.DrawableRef().SetLayer( 8 );
	pawn2.DrawableRef().SetLayer( -8 );

	while ( window.isOpen() ) {
		while ( window.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				window.close();
		}

		gTime()._update();

		if ( static bool done = false;  gTime().GetTimeMs() > 5000 && !done ) {
			scene.Kill( 0 );
			done = true;
		}
		
		if ( static bool done = false; gTime().GetTimeMs() > 6000 && !done ) {
			auto& newPawn = scene.Spawn<Pawn>();
			if ( &pawn1 == &newPawn ) // not guaranteed to be true. Use unique ids instead storing pointers.
				LOG_INFO( "&pawn1 == &newPawn => reusing memory in this case." );
			newPawn.DrawableRef().RectangleShape() = sf::RectangleShape( { 64,64 } );
			newPawn.DrawableRef().RectangleShape().setFillColor( sf::Color::Cyan );
			newPawn.ResetController<TestController>();
			done = true;
		}

		//LOG_INFO( 1 / gTime().GetFrameDelta(), "fps" );
		
		scene.Update();

		window.clear();
		scene.Draw( window );
		window.display();
	}
}