/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"

// for exist(path) in Save()
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <iterator>

#include "../Inc/INIFile.hpp"
#include "../Inc/Guideline.hpp"
#include "../Inc/Debug.hpp"

namespace con
{

bool INIFile::Open( const std::string& name )
{
	std::fstream file( name );
	
	if ( !file ) {
		LOG_ERROR( "Cannot open INIFile: ", name );
		return false;
	}

	this->Clear();
	this->pathToFile = name;

	std::string line = "";
	while ( !file.eof() ) {
		std::getline( file, line );
		if ( line.empty() ) // don't want empty lines
			continue;

		this->rawData.push_back( line );
	}

	Ensures( !this->rawData.empty() );

	return true;
}

bool INIFile::Save( const std::string& path, bool override )
{
	if ( Expects( !path.empty() && !this->parsedData.empty() ).Failed() ) {
		return false;
	}
	this->pathToFile = path;

	std::vector<std::string> serializeData;
	this->makeSerializeData( serializeData );


	if ( std::experimental::filesystem::exists( "./" + path ) &&
		 !override )
		return false;

	std::experimental::filesystem::remove( path );
	std::ofstream file( this->pathToFile );
	std::copy( serializeData.begin(), serializeData.end(),
			   std::ostream_iterator<std::string>( file, "\n" ) );

	return true;
}

void INIFile::Parse()
{
	this->parsedData.clear();
	this->parsedData.reserve( this->rawData.size() );
	record_t tempRecord;
	std::string& section = tempRecord.section;
	std::string& name = tempRecord.name;
	std::string& value = tempRecord.value;
	std::string tempString;

	for ( const auto& str : this->rawData ) {
		if ( str.front() == ';' ) // ; - comment sign
			continue;

		tempString = str;
		// Removing blank spaces before name and after value (   name = value   )
		//													  ^^^            ^^^
		while ( tempString.front() == ' ' || tempString.front() == '\t' )
			tempString.erase( tempString.begin() );
		while ( tempString.back() == ' ' || tempString.back() == '\t' )
			tempString.pop_back();

		if ( tempString.find_first_of( '=' ) == std::string::npos ) // If there is no '=' then parse as Section
			section = parseAsSection( tempString );
		else {
			name = str.substr( 0, str.find_first_of( '=' ) );
			value = str.substr( str.find_first_of( '=' ) + 1 );

			// Removing blank after before name and before value (name   =   value)
			//														  ^^^ ^^^
			while ( name.back() == ' ' || name.back() == '\t' )
				name.pop_back();
			while ( value.front() == ' ' || value.front() == '\t' )
				value.erase( value.begin() );

			this->parsedData.push_back( tempRecord );
		}
	}

	this->parsedData.shrink_to_fit();
}

void INIFile::Clear()
{
	this->rawData.clear();
	this->parsedData.clear();
}

std::optional<INIFile::stringRef_t> INIFile::GetValue( const std::string& section, const std::string& name )
{
	auto result = std::find_if( this->parsedData.begin(), this->parsedData.end(),
								[section, name]( auto& record ) {
		return ( record.section == section ) && ( record.name == name );
	} );

	if ( result != this->parsedData.end() )
		return result->value;

	return {};
}

std::vector<INIFile::record_t>& INIFile::GetParsedData()
{
	return this->parsedData;
}

std::string& INIFile::GetPath()
{
	return this->pathToFile;
}

void INIFile::AddValue( const std::string& section, const std::string& name, const std::string& value )
{
	this->parsedData.emplace_back( record_t{ section, name, value } );
}

std::string INIFile::parseAsSection( const std::string& str )
{
	Expects( str.front() == '[' && str.back() == ']' );

	// Starting from 1 for '['; -1 for \0 and -1 for ']'
	return str.substr( 1, str.size() - 1 - 1 );
}

void INIFile::makeSerializeData( std::vector<std::string>& to )
{
	to.clear();
	to.reserve( this->parsedData.size() );

	std::string section = "";
	for ( const auto& record : this->parsedData ) {
		if ( record.section != section ) {
			if ( section.empty() ) // If it's first section name then don't add '\n' at the beginning
				to.push_back( "[" + record.section + "]" );
			else
				to.push_back( "\n[" + record.section + "]" );

			section = record.section;
		}

		to.push_back( record.name + " = " + record.value );
	}
}
}