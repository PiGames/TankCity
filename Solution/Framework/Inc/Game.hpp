/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Logger.hpp"
#include "Messaging.hpp"
#include "StateStack.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace con
{
/* Handles basic input, drawing and has main loop. Loads config and makes
	window.
*/
class Game final :
	public Single<Game>
{
public:
	Game( std::string&& configFilePath );
	~Game();

	template <typename TState>
	void RegisterState( stateID id );

	void Run( stateID initState );

private:
	// Context points to these fields.
	Logger logger;
	Time time;
	Messenger messenger;

	sf::RenderWindow window;
	bool exit = false;
	StateStack stateStack;

	void handleInput( sf::Event& event );
	void update();
	void draw();
};
}

#include "../Src/Game.inl"