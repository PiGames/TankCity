/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma warning(push)
// Something about const arguments - it wants to TArgs&& be const!
#pragma warning(disable:26461)

namespace con
{
template <typename T, typename ...TArgs>
inline void Logger::Log( LogLevel level, const T& val, TArgs&& ...args )
{
	std::string programUpTime = Time::Format( gTime().SinceAppStartMs() );

	auto msg = To<std::string>( "[", programUpTime, "| ", this->getLogLevelAsStr( level ), "] " );
	msg += To<std::string>( val, std::forward<TArgs>( args )... );

	{
		std::scoped_lock<std::mutex> lock{ this->messageQueueMutex };
		this->messageQueue.push( msg );
	}
}
}

#pragma warning(pop)
