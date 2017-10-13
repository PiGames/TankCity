/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

#include "Conversions.hpp"
#include "Debug.hpp"
#include "Single.hpp"

namespace con
{
using resourceID = uint16;

static_assert( std::is_default_constructible_v<sf::Texture>	&&
			   std::is_default_constructible_v<sf::Font> &&
			   std::is_default_constructible_v<sf::SoundBuffer> &&
			   std::is_default_constructible_v<sf::Music>,
			   "SFML Resources not default constructible?" );

/* Class for storing Textures, Fonts, Sounds and Music.
*/
class ResourceHolder final :
	public Single<ResourceHolder>
{
	template <typename T>
	using ResourceMap = std::unordered_map<resourceID, T>;

public:
	sf::Texture& AddTexture( resourceID id );
	sf::Font& AddFont( resourceID id );
	sf::SoundBuffer& AddSoundBuffer( resourceID id );
	sf::Music& AddMusic( resourceID id );

	sf::Texture& GetTexture( resourceID id );
	sf::Font& GetFont( resourceID id );
	sf::SoundBuffer& GetSoundBuffer( resourceID id );
	sf::Music& GetMusic( resourceID id );

	/* Templated version of AddXXX(id).
	*/
	template <typename T>
	T& Add( resourceID id );

	/* Templated version of GetXXX(id).
		Usage: Get<ResourceTexture>( TEXTURE_PLAYER )
		Where TEXTURE_PLAYER is an enum.
	*/
	template <typename T>
	T& Get( resourceID id );

	/* Templated version of GetFallbackXXX.
		Returns reference to fallback object that is returned if Get() cannot return
		invalid asset (if it doesn't exist for example).
		Usage: GetFallbackResource<ResourceTexture>
	*/
	template <typename T>
	T& GetFallbackResource();

private:
	ResourceMap<sf::Texture> textures;
	ResourceMap<sf::Font> fonts;
	ResourceMap<sf::SoundBuffer> soundBuffs;
	ResourceMap<sf::Music> music;
	sf::Texture fallbackTexture;
	sf::Font fallbackFont;
	sf::SoundBuffer fallbackSoundBuff;
	sf::Music fallbackMusic;

	template <typename T>
	auto& getStorageByType(); // is it valid?

	template <typename T>
	constexpr const char* getTemplateResTypeAsStr();
};
}

#include "../Src/Resource.inl"