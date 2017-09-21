/*
	Untitled_Guys 2017
	https://github.com/UntitledGuys/
*/

#include "Actor.hpp"
#include "Context.hpp"
#include "Logger.hpp"

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

	testActor.GetDrawableRef().GetVariantRef() = sf::Sprite( tex );

	while ( window.isOpen() ) {
		while ( window.pollEvent( ev ) ) {
			if ( ev.type == sf::Event::Closed )
				window.close();
		}

		testActor.Move( Vec2f::UP * 0.1 );
		testActor.Update();

		window.clear();
		testActor.Draw( window );
		window.display();
	}
}