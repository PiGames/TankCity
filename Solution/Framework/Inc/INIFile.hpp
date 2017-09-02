/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <functional>

namespace con
{

/*	Class created for manipulating INI files. Remember that you must Parse the
	file after you open it. If you leave Save() to default it will override
	opened file.
*/
class INIFile final
{
public:
	struct record_t final
	{
		std::string section{}, name{}, value{};
	};
	using stringRef_t = std::reference_wrapper<std::string>;

	bool Open( const std::string& path );
	bool Save( const std::string& path = "", bool override = true );
	void Parse();
	void Clear();

	/* Returns std::optional<stringRef_t>, where stringRef_t is std::reference_wrapper<std::string>.
	*/
	std::optional<stringRef_t> GetValue( const std::string& section, const std::string& name );
	std::vector<record_t>& GetParsedData();
	std::string& GetPath();

	void AddValue( const std::string& section, const std::string& name, const std::string& value );

private:
	std::string pathToFile = "";
	std::vector<std::string> rawData;
	std::vector<record_t> parsedData;

	std::string parseAsSection( const std::string& str );
	void makeSerializeData( std::vector<std::string>& to );
};
}