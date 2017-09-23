/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Debug.hpp"
#include "../Inc/Game.hpp"
#include "../Inc/Messages.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

namespace con
{

Game::Game( std::string&& configFilePath )
{
	// TODO: Add INIFile and read from config here.
	(void)configFilePath;

	this->window.create( { 800,600 }, "ConFramework", sf::Style::Close );
	this->window.setFramerateLimit( 60 );

#pragma warning(push)
#pragma warning(disable:26425) // Assigning *this to static variable. 
	Context::logger = &this->logger;
	Context::time = &this->time;
	Context::messenger = &this->messenger;
#pragma warning(pop)
	gLogger().SetConsoleOutputStream( &std::cout );

	LOG_INFO( "Game ctor" );
}

Game::~Game()
{
	// TODO: Save current config here.
	LOG_INFO( "Game dtor" );
}

void Game::Run( stateID initState )
{
	sf::Event event{};

	gMessenger().Add<statePushMessage>( initState, To<int16>( frameworkMessages_t::STATE_PUSH ) );

	while ( !this->exit ) {
		this->handleInput( event );
		this->update();
		this->draw();
	}
}

void Game::handleInput( sf::Event& event )
{
	while ( window.pollEvent( event ) ) {
		if ( sf::Event::Closed == event.type ) {
			this->exit = true;
			return;
		}

		if ( this->window.hasFocus() )
			gMessenger().Add<inputMessage>( event, To<int16>( frameworkMessages_t::INPUT ) );
	}
}

void Game::update()
{
	this->time._update();
	this->messenger.SwapBuffers();
	this->stateStack.Update();
	if ( messenger.GetOne<exitMessage>( To<int16>( frameworkMessages_t::EXIT ) ).has_value() )
		this->exit = true;
}

void Game::draw()
{
	this->window.clear();
	// call drawable components of entities here?
	this->window.display();
}
}