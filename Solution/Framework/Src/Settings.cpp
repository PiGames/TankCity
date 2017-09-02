/*
	Untitled_Guys 2017
	https://github.com/UntitledGuys/
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Settings.hpp"
#include "../Inc/Guideline.hpp"
#include "../Inc/Debug.hpp"

namespace con
{
using record_t = Settings::record_t;
using stringRef_t = Settings::stringRef_t;

bool Settings::AddDefault( const record_t& record )
{
	if ( Expects( !record.section.empty() ).Failed() )
		return false;
	if ( Expects( !record.name.empty() ).Failed() )
		return false;
	if ( Expects( !record.value.empty() ).Failed() )
		return false;

	this->defaultSettings.push_back( record );
	LOG_INFO( "Default settings added: ", record.section, ", ", record.name, ", ", record.value );

	return true;
}

std::optional<stringRef_t> Settings::Get( const std::string& section, const std::string& name )
{
	if ( Expects( !section.empty() ).Failed() )
		return {};
	if ( Expects( !name.empty() ).Failed() )
		return {};

	return this->cfgFile.GetValue( section, name );
}

std::optional<stringRef_t> Settings::GetDefault( const std::string& section, const std::string& name )
{
	if ( Expects( !section.empty() ).Failed() )
		return {};
	if ( Expects( !name.empty() ).Failed() )
		return {};

	auto result = std::find_if( this->defaultSettings.begin(), this->defaultSettings.end(),
								[&]( const auto& record ) {
		return record.section == section && record.name == name;
	} );

	if ( result != this->defaultSettings.end() )
		return { result->value };

	return {};
}

bool Settings::Open( const std::string& path )
{
	if ( const auto ok = this->cfgFile.Open( path ); !ok )
		return false;

	this->cfgFile.Parse();

	if ( !this->defaultSettings.empty() ) {
		if ( Expects( !this->checkIfMatchesDefault() ).Failed() )
			this->generateDefault();
	}

	return true;
}

bool Settings::Save()
{
	return this->cfgFile.Save();
}

bool Settings::checkIfMatchesDefault()
{
	const auto& file = this->cfgFile.GetParsedData();
	const auto& default = this->defaultSettings;

	if ( default.size() > file.size() ) {
		return false;
	}

	return std::equal(
		default.begin(), default.end(),
		file.begin(), file.begin() + default.size(),
		[]( const auto& recordA, const auto& recordB ) {
		return recordA.section == recordB.section && recordA.name == recordB.name;
	} );
}

void Settings::generateDefault()
{
	this->cfgFile.Clear();
	const auto& defaults = this->defaultSettings;
	auto& fileSettings = this->cfgFile.GetParsedData();
	fileSettings.clear();

	std::copy( defaults.cbegin(), defaults.cend(), std::back_inserter( fileSettings ) );
}
}