/*
	Untitled_Guys 2017
*/

#include "INIFile.hpp"
#include "Conversions.hpp"
#include "Debug.hpp"
#include <iostream>
#include <filesystem> // delete file after test

using namespace con;

static void Init()
{
	static Time time;
	static Logger logger;
	logger.SetConsoleOutputStream( &std::cout );
	Context::time = &time;
	Context::logger = &logger;
}

constexpr const char* FILE_PATH = "initest.ini";

void Save();
void Open();

int main()
{
	Init();
	Save();
	Open();
	LOG_INFO( "Press ENTER to delete test file ", FILE_PATH );
	std::cin.get();

	std::experimental::filesystem::remove( { FILE_PATH } );
}

void Save()
{
	INIFile file;
	file.AddValue( "INTS", "int8", "8" );
	file.AddValue( "INTS", "int16", "16" );
	file.AddValue( "INTS", "int32", "32" );
	file.AddValue( "INTS", "int64", "64" );
	file.AddValue( "OTHERS", "float32", "32" );
	file.AddValue( "OTHERS", "float64", "64" );
	file.AddValue( "OTHERS", "bool", "true" );
	file.Save( FILE_PATH );
}

void Open()
{
	INIFile file;
	file.Open( FILE_PATH );
	file.Parse();
	std::string fuck = "fucking fuck";
	auto fucks = std::ref( fuck );

	LOG_INFO( "INTS | int8: ", file.GetValue( "INTS", "int8" ).value_or( fucks ).get() );
	LOG_INFO( "INTS | int16: ", file.GetValue( "INTS", "int16" ).value_or( fucks ).get() );
	LOG_INFO( "INTS | int32: ", file.GetValue( "INTS", "int32" ).value_or( fucks ).get() );
	LOG_INFO( "INTS | int64: ", file.GetValue( "INTS", "int64" ).value_or( fucks ).get() );
	LOG_INFO( "OTHERS | float32: ", file.GetValue( "OTHERS", "float32" ).value_or( fucks ).get() );
	LOG_INFO( "OTHERS | float64: ", file.GetValue( "OTHERS", "float64" ).value_or( fucks ).get() );
	LOG_INFO( "OTHERS | bool: ", file.GetValue( "OTHERS", "bool" ).value_or( fucks ).get() );
}
