/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"

#include "../Inc/Logger.hpp"

namespace con
{
Logger::Logger() :
	leaveMessageSavingThread( false ),
	messageSavingThread( &Logger::messageSavingThreadLoop, this ),
	Single<Logger>()
{}

Logger::~Logger()
{
	this->leaveMessageSavingThread = true;
	this->messageSavingThread.join();

	if ( this->fileStream )
		this->fileStream->flush();
}

void Logger::SetConsoleOutputStream( std::ostream* stream )
{
	this->consoleStream = stream;
}

void Logger::SetFileOutputStream( std::ostream* stream )
{
	this->fileStream = stream;
}

const char* Logger::getLogLevelAsStr( LogLevel level ) const
{
	switch ( level ) {
	case LogLevel::INFO: return		"INFO   ";
	case LogLevel::WARNING: return	"WARNING";
	case LogLevel::ERROR: return	"ERROR  ";
	}

	return "";
}

void Logger::messageSavingThreadLoop()
{
	Timer fileFlushTimer;

	while ( !this->leaveMessageSavingThread ) {
		if ( this->messageQueue.empty() )
			continue;
		std::string strToSave;
		{
			std::scoped_lock<std::mutex> lock{ this->messageQueueMutex };
			strToSave = this->messageQueue.front() + '\n';
			this->messageQueue.pop();
		}

		if ( this->consoleStream )
			*this->consoleStream << strToSave;

		if ( this->fileStream ) {
			*this->fileStream << strToSave;
			if ( fileFlushTimer.GetMilliseconds() >= 500 ) {
				fileFlushTimer.Reset();
				this->fileStream->flush();
			}
		}
	}
}
}