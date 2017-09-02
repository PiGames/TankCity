/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma warning(push)
// Something about const arguments - it wants to TArgs&& be const!
#pragma warning(disable:26461)

template <typename ...TArgs>
inline void LOG_INFO( TArgs&& ...args )
{
	con::gLogger().Log( con::LogLevel::INFO, std::forward<TArgs>( args )... );
}

template <typename ...TArgs>
inline void LOG_WARN( TArgs&& ...args )
{
	con::gLogger().Log( con::LogLevel::WARNING, std::forward<TArgs>( args )... );
}

template <typename ...TArgs>
inline void LOG_ERROR( TArgs&& ...args )
{
	con::gLogger().Log( con::LogLevel::ERROR, std::forward<TArgs>( args )... );
}

template <typename ...TArgs>
inline void LOG_INFO_D( TArgs&& ...args )
{
	if constexpr(IS_DEBUG)
		con::gLogger().Log( con::LogLevel::INFO, std::forward<TArgs>( args )... );
	else
		con::consume_args{ args... };
}

template <typename ...TArgs>
inline void LOG_WARN_D( TArgs&& ...args )
{
	if constexpr(IS_DEBUG)
		con::gLogger().Log( con::LogLevel::WARNING, std::forward<TArgs>( args )... );
	else
		con::consume_args{ args... };
}

template <typename ...TArgs>
inline void LOG_ERROR_D( TArgs&& ...args )
{
	if constexpr(IS_DEBUG)
		con::gLogger().Log( con::LogLevel::ERROR, std::forward<TArgs>( args )... );
	else
		con::consume_args{ args... };
}

#pragma warning(pop)