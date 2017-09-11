// Need to redo it.
#if 0

/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Core.hpp"
#include "Conversions.hpp"
#include "Debug.hpp"
#include "Single.hpp"

/* Idea for this classes is that if in future I would have
	a custom Api that is not SFML that it will be easier to implement it
	to current code.
*/

namespace con
{
using resourceID_t = uint16_t;

/* Virtual class for GenericResource and MusicResource. Has Get and GetPtr methods.
*/
template <typename T>
class Resource
{
public:
	virtual ~Resource() = default;

	const T& Get() const
	{
		return this->resource;
	}
	T& Get()
	{
		return this->resource;
	}
	const T* GetPtr() const
	{
		return &this->resource;
	}
	T* GetPtr()
	{
		return &this->resource;
	}

protected:
	T resource;
};

/* Inherit from this to implement basic resource class: Texture, Font and SoundBuffer.
	To implement Music inherit from MusicResource<T>.
*/
template <typename T>
class GenericResource :
	public Resource<T>
{
public:
	virtual ~GenericResource() = default;

	virtual bool LoadFromFile( const std::string& path ) = 0;
};

/* Inherit from this to implement music resource class: .
	To implement Texture, Font or Sound inherit from GenericResource<T>.
*/
template <typename T>
class MusicResource :
	public Resource<T>
{
public:
	virtual ~MusicResource() = default;

	virtual bool OpenFromFile( const std::string& path ) = 0;

	//virtual bool Opened() const = 0; // Is it needed?
	virtual bool Playing() const = 0;
	virtual bool Paused() const = 0;

	virtual void Play() = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
};

/* Class for storing Textures, Fonts, Sounds and Music.
	Declaration: ResourceHolder<ApiTexture, ApiFont, ApiSound, ApiMusic,
				ResourceTexture, ResourceFont, ResourceSound, ResourceMusic>
	Where ResorceXXX inherits from MusicResource or GenericResource.
*/
template
<typename TextureType, typename FontType, typename SoundBuffType, typename MusicType,
	typename TextureResourceType = GenericResource<TextureType>,
	typename FontResourceType = GenericResource<FontType>,
	typename SoundBuffResourceType = GenericResource<SoundBuffType>,
	typename MusicResourceType = MusicResource<MusicType>>
	class ResourceHolder final :
	public Single
	<ResourceHolder <TextureType, FontType, SoundBuffType, MusicType,
	TextureResourceType, FontResourceType, SoundBuffResourceType, MusicResourceType>>
{
	template <typename T>
	using ResourceMap = std::unordered_map<resourceID_t, T>;

public:
	template <typename T>
	T& Add( resourceID_t id )
	{
		auto& map = this->getStorageByType<T>();

		// Emplace empty (default - constructed) resource.
		auto emplaced = map.try_emplace( id, T() );

		// true if emplaced
		if ( !emplaced.second )
			LOG_WARN( this->getTemplateResTypeAsStr<T>(), " of id ", id, " already exists" );

		return emplaced.first->second;
	}

	/* Usage: Get<ResourceTexture>( TEXTURE_PLAYER )
		Where TEXTURE_PLAYER is an enum.
	*/
	template <typename T>
	auto& Get( resourceID_t id )
	{
		auto& map = this->getStorageByType<T>();
		auto result = map.find( id );
		bool found = result != map.end();

		if ( found )
			return result->second;
		else {
			LOG_ERROR( "Missing ", this->getTemplateResTypeAsStr<T>(), " of id ", id );
			return getFallbackByType<T>();
		}
	}

	/* Returns reference to fallback object that is returned if Get() cannot return
		invalid asset (if it doesn't exist for example).
		Usage: GetFallbackResource<ResourceTexture>
	*/
	template <typename T>
	auto& GetFallbackResource()
	{
		return this->getFallbackByType<T>();
	}

private:
	ResourceMap<TextureResourceType> textures;
	ResourceMap<FontResourceType> fonts;
	ResourceMap<SoundBuffResourceType> soundBuffs;
	ResourceMap<MusicResourceType> music;
	TextureResourceType fallbackTexture;
	FontResourceType fallbackFont;
	SoundBuffResourceType fallbackSoundBuff;
	MusicResourceType fallbackMusic;

	template <typename T>
	constexpr auto& getStorageByType()
	{
		if constexpr ( IsSameType<TextureResourceType, T> )
			return this->textures;
		else if constexpr ( IsSameType<FontResourceType, T> )
			return this->fonts;
		else if constexpr ( IsSameType<SoundBuffResourceType, T> )
			return this->soundBuffs;
		else if constexpr ( IsSameType<MusicResourceType, T> )
			return this->music;
	}

	template <typename T>
	constexpr auto& getFallbackByType()
	{
		if constexpr ( IsSameType<TextureResourceType, T> )
			return this->fallbackTexture;
		else if constexpr ( IsSameType<FontResourceType, T> )
			return this->fallbackFont;
		else if constexpr ( IsSameType<SoundBuffResourceType, T> )
			return this->fallbackSoundBuff;
		else if constexpr ( IsSameType<MusicResourceType, T> )
			return this->fallbackMusic;
	}

	template <typename T>
	constexpr const char* getTemplateResTypeAsStr() const
	{
		if constexpr ( IsSameType<TextureResourceType, T> )
			return "Texture";
		else if constexpr ( IsSameType<FontResourceType, T> )
			return "Font";
		else if constexpr ( IsSameType<SoundBuffResourceType, T> )
			return "Sound Buffer";
		else if constexpr ( IsSameType<MusicResourceType, T> )
			return "Music";
	}

	bool alreadyAdded( resourceID_t id )
	{
		auto result = std::find( this->resourcesAlreadyAdded.begin(), this->resourcesAlreadyAdded.end(), id );
		return result != this->resourcesAlreadyAdded.end();
	}
};
}

#endif