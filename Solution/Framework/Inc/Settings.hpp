/*
	Untitled_Guys 2017
*/

#pragma once

#include <optional>

#include "INIFile.hpp"
#include "Single.hpp"

namespace con
{
/* Contains current and default settings for whole application.
	Can be accesed using gSettings() defined in Context.hpp.
	You shouldn't use Open and Save - they are called by Game
	in ctor and dtor.
*/
class Settings final :
	public Single<Settings>
{
public:
	using record_t = INIFile::record_t;
	using stringRef_t = INIFile::stringRef_t;

	bool AddDefault( const record_t& record );
	std::optional<stringRef_t> Get( const std::string& section, const std::string& name );
	std::optional<stringRef_t> GetDefault( const std::string& section, const std::string& name );

	bool Open( const std::string& path );
	bool Save();

private:
	std::vector<record_t> defaultSettings;
	INIFile cfgFile;

	bool checkIfMatchesDefault();
	void generateDefault();
};
}