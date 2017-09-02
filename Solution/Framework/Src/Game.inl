/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

namespace con
{
template<typename TState>
inline void Game::RegisterState( stateID_t id )
{
	this->stateStack.RegisterState<TState>( id );
}
}