// Need to redo it.
#if 0
/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../../Core/Include/Resource.hpp"

#include <iostream>

using namespace con;

struct texture_t
{
	int data = 0;
};

struct font_t
{
	int data = 1;
};

struct sound_t
{
	int data = 2;
};

struct music_t
{
	int data = 3;
};

class TextureResource :
	public GenericResource<texture_t>
{
public:
	bool LoadFromFile( const std::string& path ) override
	{
		LOG_INFO( "Loading texture_t: ", path );
		return true;
	}
};

class FontResource :
	public GenericResource<font_t>
{
public:
	bool LoadFromFile( const std::string& path ) override
	{
		LOG_INFO( "Loading font_t: ", path );
		return true;
	}
};

class SoundResource :
	public GenericResource<sound_t>
{
public:
	bool LoadFromFile( const std::string& path ) override
	{
		LOG_INFO( "Loading sound_t: ", path );
		return true;
	}
};

class MusicRes :
	public MusicResource<music_t>
{
public:
	bool OpenFromFile( const std::string& path ) override
	{
		LOG_INFO( "Opening music_t: ", path );
		return true;
	}

	bool Playing() const override
	{
		LOG_INFO( "Playing() (false)" );
		return false;
	}
	bool Paused() const override
	{
		LOG_INFO( "Paused() (false)" );
		return false;
	}

	void Play() override
	{
		LOG_INFO( "Play()" );
	}
	void Pause() override
	{
		LOG_INFO( "Pause()" );
	}
	void Stop() override
	{
		LOG_INFO( "Stop()" );
	}
};

int main()
{
	con::Logger logger;
	con::Time time;
	logger.SetConsoleOutputStream( &std::cout );
	con::Context::logger = &logger;
	con::Context::time = &time;

	ResourceHolder<texture_t, font_t, sound_t, music_t,
		TextureResource, FontResource, SoundResource, MusicRes>
		resourceHolder;

	resourceHolder.Add<TextureResource>( 0 ).LoadFromFile( "texture" );
	resourceHolder.Add<FontResource>( 1 ).LoadFromFile( "font" );
	resourceHolder.Add<SoundResource>( 2 ).LoadFromFile( "sound" );
	resourceHolder.Add<MusicRes>( 3 ).OpenFromFile( "music" );

	auto& texture = resourceHolder.Get<TextureResource>( 0 );
	auto& font = resourceHolder.Get<FontResource>( 1 );
	auto& sound = resourceHolder.Get<SoundResource>( 2 );
	auto& music = resourceHolder.Get<MusicRes>( 3 );

	LOG_INFO( "texture = ", texture.Get().data );
	LOG_INFO( "font    = ", font.Get().data );
	LOG_INFO( "sound   = ", sound.Get().data );
	LOG_INFO( "music   = ", music.Get().data );

	resourceHolder.GetFallbackResource<TextureResource>().Get().data = 100;
	resourceHolder.GetFallbackResource<FontResource>().Get().data = 200;
	resourceHolder.GetFallbackResource<SoundResource>().Get().data = 300;
	resourceHolder.GetFallbackResource<MusicRes>().Get().data = 400;


	// Test catching missing assets
	LOG_INFO( "texture = ", resourceHolder.Get<TextureResource>( 3 ).Get().data, " (100)" );
	LOG_INFO( "font    = ", resourceHolder.Get<FontResource>( 2 ).Get().data, "(200)" );
	LOG_INFO( "sound   = ", resourceHolder.Get<SoundResource>( 1 ).Get().data, "(300)" );
	LOG_INFO( "music   = ", resourceHolder.Get<MusicRes>( 0 ).Get().data, "(400)" );

	// Test adding same asserts
	resourceHolder.Add<TextureResource>( 0 ).LoadFromFile( "texture" );
	resourceHolder.Add<FontResource>( 1 ).LoadFromFile( "font" );
	resourceHolder.Add<SoundResource>( 2 ).LoadFromFile( "sound" );
	resourceHolder.Add<MusicRes>( 3 ).OpenFromFile( "music" );

	std::cin.get();
	return 0;
}

#endif