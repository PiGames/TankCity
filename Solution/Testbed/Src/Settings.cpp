/*
	Untitled_Guys 2017
*/

#include "Settings.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

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

const std::string FILE_PATH = "config.ini";

int main()
{
	Init();
	Settings settings;

	settings.AddDefault( { "WINDOW", "SIZE_X", "1280" } );
	settings.AddDefault( { "WINDOW", "SIZE_Y", "720" } );
	settings.AddDefault( { "WINDOW", "FPS", "60" } );

	settings.Open( FILE_PATH );

	LOG_INFO( "[WINDOW] SIZE_X = ", settings.Get( "WINDOW", "SIZE_X" ).value().get() );
	LOG_INFO( "[WINDOW] SIZE_Y = ", settings.Get( "WINDOW", "SIZE_Y" ).value().get() );
	LOG_INFO( "[WINDOW] FPS = ", settings.Get( "WINDOW", "FPS" ).value().get() );
	LOG_INFO( "Press ENTER to delete test file ", FILE_PATH );

	settings.Save();
	std::cin.get();
	std::experimental::filesystem::remove( { FILE_PATH } );
}