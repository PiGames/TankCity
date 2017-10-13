/*
	Untitled_Guys 2017
*/

namespace con
{
template <typename T>
T& ResourceHolder::Add( resourceID id )
{
	auto& map = this->getStorageByType<T>();

	// Emplace empty (default - constructed) resource.
	auto tryResult = map.try_emplace( id );

	// true if emplaced
	if ( !tryResult.second ) {
		LOG_WARN( "Failed to emplace ", this->getTemplateResTypeAsStr<T>(), " of id ", id );
		return this->GetFallbackResource<T>();
	}

	return tryResult.first->second;
}

template <typename T>
T& ResourceHolder::Get( resourceID id )
{
	auto& map = this->getStorageByType<T>();
	auto result = map.find( id );
	bool found = result != map.end();

	if ( !found ) {
		LOG_ERROR( "Missing ", this->getTemplateResTypeAsStr<T>(), " of id ", id );
		return this->GetFallbackResource<T>();
	}

	return result->second;
}

template <typename T>
T& ResourceHolder::GetFallbackResource()
{
	if constexpr ( std::is_same_v<sf::Texture, T> )
		return this->fallbackTexture;
	else if constexpr ( std::is_same_v<sf::Font, T> )
		return this->fallbackFont;
	else if constexpr ( std::is_same_v<sf::SoundBuffer, T> )
		return this->fallbackSoundBuff;
	else if constexpr ( std::is_same_v<sf::Music, T> )
		return this->fallbackMusic;
}

template <typename T>
auto& ResourceHolder::getStorageByType()
{
	if constexpr ( std::is_same_v<sf::Texture, T> )
		return this->textures;
	else if constexpr ( std::is_same_v<sf::Font, T> )
		return this->fonts;
	else if constexpr ( std::is_same_v<sf::SoundBuffer, T> )
		return this->soundBuffs;
	else if constexpr ( std::is_same_v<sf::Music, T> )
		return this->music;
}

template <typename T>
constexpr const char* ResourceHolder::getTemplateResTypeAsStr()
{
	if constexpr ( std::is_same_v<sf::Texture, T> )
		return "Texture";
	else if constexpr ( std::is_same_v<sf::Font, T> )
		return "Font";
	else if constexpr ( std::is_same_v<sf::SoundBuffer, T> )
		return "Sound Buffer";
	else if constexpr ( std::is_same_v<sf::Music, T> )
		return "Music";
}
}