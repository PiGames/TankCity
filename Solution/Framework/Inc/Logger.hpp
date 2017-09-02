/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "PCH.hpp"
#include "Context.hpp"
#include "Conversions.hpp"
#include "Single.hpp"
#include "Time.hpp"
#include "Misc.hpp"

namespace con
{
enum class LogLevel
{
	INFO,
	WARNING,
	ERROR
};

/* Class for logging purpose.
*/
class Logger final :
	public Single<Logger>
{
public:
	Logger();
	~Logger();

	/*					  \/ INFO, WARNING, ERROR
	  Writes: [hh:mm:ss][LogLevel] str
		  ^program up time	 ^message, changes every '%d' to matching argument
	*/
	template <typename T, typename ...TArgs>
	void Log( LogLevel level, const T& val, TArgs&& ...args );

	/* Set at beginning of the program, std::cout for default
	*/
	void SetConsoleOutputStream( std::ostream* stream );
	/* Set at beggining of the program. Stream (file) must be valid all the time.
	*/
	void SetFileOutputStream( std::ostream* stream );

private:
	std::queue<std::string> messageQueue;
	std::thread messageSavingThread;
	bool leaveMessageSavingThread;
	std::mutex messageQueueMutex;
	std::ostream* consoleStream = nullptr, *fileStream = nullptr;

	const char* getLogLevelAsStr( LogLevel level ) const;

	void messageSavingThreadLoop();
};
}

#include "../Src/Logger.inl"
