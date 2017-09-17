/*
	Untitled_Guys 2017
	https://github.com/UntitledGuys/
*/

#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Audio/Music.hpp>


class ResourceHolder
{
	public:
		static ResourceHolder& Instance()
		{
			static ResourceHolder ins;
			return ins;
		}

		//~ResourceHolder();
		template<class T>
		static T* Load( const std::string& name, const std::string& path )
		{
			return SourceCache<T>::Load( name, path );
		}

		template<class T>
		static T* Get( const std::string& name )
		{
			return SourceCache<T>::Get( name );
		}

		template<class T>
		static std::size_t Cleanup()
		{
			return SourceCache<T>::Cleanup();
		}

	private:
		ResourceHolder();
		ResourceHolder( const ResourceHolder& );

};

template<class T>
class SourceCache
{
	public:
		SourceCache( const SourceCache& ) = delete;
		void operator=( const SourceCache& ) = delete;

		static T* Load( const std::string& name, const std::string& path )
		{
			T* result = SourceCache::Get( name );

			if ( result ) {
				if constexpr ( std::is_same<T, sf::Music>::value ) {
					result->openFromFile( path );
				} else {
					result->loadFromFile( path );
				}
			}
			else {
				result = new T();
				if constexpr ( std::is_same<T, sf::Music>::value ) {
					result->openFromFile( path );
				} else {
					result->loadFromFile( path );
				}
				SourceCache::Instance().cache[name] = result;
			}
			return result;
		}

		static bool Unload(const std::string& name)
		{
			auto& instance = Instance();
			auto iterator = instance.cache.find( name );

			if ( iterator == instance.cache.end() ) {
				return false;
			}
			else {
				delete ( iterator->second );
				instance.cache.erase( iterator );
				return true;
			}
		}

		static T* Get( const std::string& name )
		{
			auto& instance = SourceCache::Instance();
			auto iterator = instance.cache.find( name );
			
			if ( iterator == instance.cache.end() ) {
				return nullptr;
			}

			return iterator->second;
		}

		static std::size_t Cleanup()
		{
			auto &instance = Instance();

			std::size_t count = instance.cache.size();

			for (auto data : instance.cache)
			{
				delete (data.second);
			}

			return count;
		}

	private:
		SourceCache() = default;
		inline static SourceCache& Instance()
		{
			static SourceCache ins;
			return ins;
		}

		std::unordered_map<std::string, T*> cache;
};
