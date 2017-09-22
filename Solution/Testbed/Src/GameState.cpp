#include "../../Framework/Inc/Game.hpp"
#include "../../Framework/Inc/State.hpp"
#include "../../Framework/Inc/Messages.hpp"

#include <iostream>

enum class state_t
{
	StateA,
	StateB
};

class StateA final :
	public con::State
{
	con::stateID GetID() const override
	{
		return con::To<con::stateID>( state_t::StateA );
	}

	void OnPush() override
	{
		LOG_INFO( "OnPush - StateA" );
		this->StartThread();
		LOG_INFO( "Thread START - StateA" );
	}
	void OnPop() override
	{
		LOG_INFO( "OnPop - StateA" );
		this->StopThread();
		LOG_INFO( "Thread STOP - StateA" );
	}
	con::Timer switchThreadTimer;

	void Update() override
	{
		if ( !this->imStateOnTopOfTheStack() )
			return;

		if ( static bool Logged = false; !Logged ) {
			LOG_INFO( "Update - StateA" );
			Logged = true;
		}

		if ( switchThreadTimer.GetMilliseconds() > 1000 )
			con::gMessenger().Add<con::statePushMessage_t>( con::To<con::stateID>( state_t::StateB ),
															con::To<con::int16>( con::frameworkMessages_t::STATE_PUSH ) );
	}
	void UpdateThread()
	{
		if ( static bool Logged = false; !Logged ) {
			LOG_INFO( "Thread - StateA" );
			Logged = true;
		}
	}
};

class StateB final :
	public con::State
{
	con::stateID GetID() const override
	{
		return con::To<con::stateID>( state_t::StateB );
	}

	void OnPush() override
	{
		LOG_INFO( "OnPush - StateB" );
		this->StartThread();
		LOG_INFO( "Thread START - StateB" );
	}
	void OnPop() override
	{
		LOG_INFO( "OnPop - StateB" );
		this->StopThread();
		LOG_INFO( "Thread STOP - StateB" );
	}
	con::Timer switchThreadTimer;
	void Update() override
	{
		if ( static bool Logged = false; !Logged ) {
			LOG_INFO( "Update - StateB" );
			Logged = true;
		}

		if ( switchThreadTimer.GetMilliseconds() > 1000 )
			con::gMessenger().Add<con::exitMessage_t>( {}, con::To<con::int16>( con::frameworkMessages_t::EXIT ) );
	}
	void UpdateThread()
	{
		if ( static bool Logged = false; !Logged ) {
			LOG_INFO( "Thread - StateB" );
			Logged = true;
		}
	}
};

int main()
{
	{
		con::Game game( "config.ini" );
		game.RegisterState<StateA>( con::To<con::stateID>( state_t::StateA ) );
		game.RegisterState<StateB>( con::To<con::stateID>( state_t::StateB ) );

		game.Run( con::To<con::stateID>( state_t::StateA ) );
	}
	std::cin.get();
}