/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

namespace con
{
template <typename TState>
inline void StateStack::RegisterState( stateID_t id )
{
	static_assert( std::is_base_of_v<State, TState>, "TState must derive from State" );
	this->factories[id] = [&]() {
		return std::make_unique<TState>();
	};
}
}