/*
	Untitled_Guys 2017
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Resource.hpp"

namespace con
{
sf::Texture& ResourceHolder::AddTexture( resourceID id )
{
	return this->Add<sf::Texture>( id );
}

sf::Font& ResourceHolder::AddFont( resourceID id )
{
	return this->Add<sf::Font>( id );
}
sf::SoundBuffer& ResourceHolder::AddSoundBuffer( resourceID id )
{
	return this->Add<sf::SoundBuffer>( id );
}

sf::Music& ResourceHolder::AddMusic( resourceID id )
{
	return this->Add<sf::Music>( id );
}

sf::Texture& ResourceHolder::GetTexture( resourceID id )
{
	return this->Get<sf::Texture>( id );
}

sf::Font& ResourceHolder::GetFont( resourceID id )
{
	return this->Get<sf::Font>( id );
}
sf::SoundBuffer& ResourceHolder::GetSoundBuffer( resourceID id )
{
	return this->Get<sf::SoundBuffer>( id );
}

sf::Music& ResourceHolder::GetMusic( resourceID id )
{
	return this->Get<sf::Music>( id );
}
}