/*
	Untitled_Guys 2017
	https://github.com/UntitledGuys/
*/

#include "Actor.hpp"
#include "Context.hpp"
#include "Debug.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

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
	
	sf::RenderWindow window( {800,600}, "Actor" );
	window.setFramerateLimit( 60 );
	sf::Event ev;
	Actor testActor(1);
	sf::Texture tex;
	sf::Image img;
	img.create( 32, 32, sf::Color::Red );
	tex.loadFromImage( img );

	auto spr = sf::Sprite( tex );
	spr.setOrigin( 16, 16 );

	testActor.DrawableRef().Sprite() = spr;
	testActor.DrawableRef().RectangleShape() = sf::RectangleShape( { 64,64 } );

	while ( window.isOpen() ) {
		while ( window.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				window.close();
		}

		testActor.Move( Vec2f::DOWN * 0.1 + Vec2f::RIGHT * 0.1 );
		testActor.Rotate( 1 );
		testActor.Update();
		LOG_INFO( "Deg: ", To<int16>(testActor.GetRotation()), " Pos: ", testActor.GetPosition() );

		window.clear();
		testActor.Draw( window );
		window.display();
	}
}