/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Resource.hpp"

#include <iostream>

using namespace con;


int main()
{
	con::Logger logger;
	con::Time time;
	logger.SetConsoleOutputStream( &std::cout );
	con::Context::logger = &logger;
	con::Context::time = &time;

	ResourceHolder resourceHolder;

	resourceHolder.AddTexture( 0 ).loadFromFile( "texture" );
	resourceHolder.AddFont( 1 ).loadFromFile( "font" );
	resourceHolder.AddSoundBuffer( 2 ).loadFromFile( "sound" );
	resourceHolder.AddMusic( 3 ).openFromFile( "music" );

	auto& texture = resourceHolder.Get<sf::Texture>( 0 );
	auto& font = resourceHolder.Get<sf::Font>( 1 );
	auto& sound = resourceHolder.Get<sf::SoundBuffer>( 2 );
	auto& music = resourceHolder.Get<sf::Music>( 3 );

	LOG_INFO( "is fallback resource used? (false)" );
	LOG_INFO( "texture = ", &texture == &resourceHolder.GetFallbackResource<sf::Texture>() );
	LOG_INFO( "font    = ", &font == &resourceHolder.GetFallbackResource<sf::Font>() );
	LOG_INFO( "sound   = ", &sound == &resourceHolder.GetFallbackResource<sf::SoundBuffer>() );
	LOG_INFO( "music   = ", &music == &resourceHolder.GetFallbackResource<sf::Music>() );

	LOG_INFO( "Test - adding same assets." );
	resourceHolder.AddTexture( 0 );
	resourceHolder.AddFont( 1 );
	resourceHolder.AddSoundBuffer( 2 );
	resourceHolder.AddMusic( 3 );

	std::cin.get();
	return 0;
}