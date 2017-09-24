/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"
#include "../Inc/State.hpp"
#include "../Inc/Debug.hpp"
#include "../Inc/Guideline.hpp"
#include "../Inc/Messaging.hpp"
#include "../Inc/Messages.hpp"

namespace con
{
State::~State()
{
	if ( this->threadIsRunning )
		this->StopThread();
}
void State::StartThread()
{
	if ( this->threadIsRunning ) {
		LOG_WARN_D( "Thread of State: ", this->GetID(), " already running, cannot start" );
		return;
	}

	this->threadIsRunning = true;
	this->thread = std::thread( &State::threadLoop, this );
}

void State::StopThread()
{
	if ( !this->threadIsRunning ) {
		LOG_WARN_D( "Thread of State: ", this->GetID(), " not running, cannot stop" );
		return;
	}

	this->threadIsRunning = false;
	this->thread.join();
}

bool State::imStateOnTopOfTheStack()
{
	const auto stateOnTop = this->getStateOnTopOfTheStack();

	return stateOnTop.value_or( ~this->GetID() ) == this->GetID();
}

std::optional<stateID> State::getStateOnTopOfTheStack()
{
	auto stateOnTopMsg = gMessenger().GetOne<stateGetOnTopMessage>( To<int16>( frameworkMessages_t::STATE_GET_ON_TOP ) );

	if ( !stateOnTopMsg.has_value() || !stateOnTopMsg.value().data.has_value() )
		return {};

	return stateOnTopMsg.value().data;
}

void State::threadLoop()
{
	while ( this->threadIsRunning )
		this->UpdateThread();
}
}