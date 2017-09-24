/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "../Inc/PCH.hpp"
#include "../Inc/StateStack.hpp"
#include "../Inc/Messaging.hpp"
#include "../Inc/Context.hpp"
#include "../Inc/Messages.hpp"


namespace con
{
constexpr int16 STATE_PUSH = static_cast<int16>( frameworkMessages_t::STATE_PUSH );
constexpr int16 STATE_POP = static_cast<int16>( frameworkMessages_t::STATE_POP );
constexpr int16 STATE_GET_ON_TOP = static_cast<int16>( frameworkMessages_t::STATE_GET_ON_TOP );

void StateStack::Update()
{
	auto orderedMessages = this->getOrderedMessages();
	if ( !orderedMessages.empty() )
		this->applyMessages( orderedMessages );

	if ( Expects( !this->stack.empty() ).Failed() )
		return;

	for ( auto& state : this->stack ) {
		state->Update();
	}

	gMessenger().Add<stateGetOnTopMessage>( this->GetStateOnTop(), STATE_GET_ON_TOP );
}

std::optional<StateStack::StatePtr> StateStack::createState( stateID id )
{
	if ( Expects( !this->factories.empty() ).Failed() )
		return {};

	const auto result = this->factories.find( id );
	if ( Ensures( result != this->factories.end() ).Failed() ) {
		LOG_ERROR( "Cannot find State of id: ", id, " (forgot to register?)" );
		return {};
	}

	return result->second();
}

StateStack::actionMessagesVector_t StateStack::getOrderedMessages()
{
	auto pushMessages = gMessenger().GetAll<statePushMessage>( STATE_PUSH );
	auto popMessages = gMessenger().GetAll<statePopMessage>( STATE_POP );
	if ( pushMessages.empty() && popMessages.empty() )
		return {};

	actionMessagesVector_t msgVec( pushMessages.size() + popMessages.size() );

	auto begin = msgVec.begin();
	for ( const auto& pushMsg : pushMessages ) {
		begin->action = action_t::PUSH;
		begin->state = pushMsg.data;
		begin->uniqueID = pushMsg.uniqueID;
		begin++;
	}
	for ( const auto& popMsg : popMessages ) {
		begin->action = action_t::POP;
		begin->state = 0;
		begin->uniqueID = popMsg.uniqueID;
		begin++;
	}

	std::sort( msgVec.begin(), msgVec.end(),
			   []( const auto& msgA, const auto& msgB ) {
		return msgA.uniqueID < msgB.uniqueID;
	} );

	return msgVec;
}

void StateStack::applyMessages( const actionMessagesVector_t& messages )
{
	for ( const auto& msg : messages ) {
		if ( msg.action == action_t::POP )
			applyPop();
		else if ( msg.action == action_t::PUSH )
			applyPush( msg );
	}
}

void StateStack::applyPop()
{
	auto stateOnTop = this->GetStateOnTop();

	if ( Expects( !stateOnTop.has_value() ).Failed() )
		return;

	LOG_INFO( "State pop, id: ", stateOnTop.value() );
	this->stack.back()->OnPop();
	this->stack.pop_back();
}

void StateStack::applyPush( const actionMessage_t& message )
{
	auto stateOnTop = this->GetStateOnTop();
	if ( Expects( !stateOnTop.has_value() ||
		 stateOnTop.value() != message.state ).Failed() )
		return;

	LOG_INFO( "State push, id: ", message.state );
	auto stateToPush = this->createState( message.state );
	if ( stateToPush.has_value() ) {
		this->stack.push_back( std::move( stateToPush.value() ) );
		this->stack.back()->OnPush();
	}
}

std::optional<stateID> StateStack::GetStateOnTop()
{
	if ( this->stack.empty() )
		return {};

	return this->stack.back()->GetID();
}
}