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

	gMessenger().Add<stateGetOnTopMessage_t>( this->GetStateOnTop(), STATE_GET_ON_TOP );
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
	auto pushMessages = gMessenger().GetAll<statePushMessage_t>( STATE_PUSH );
	auto popMessages = gMessenger().GetAll<statePopMessage_t>( STATE_POP );
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
		auto currentStateID = this->GetStateOnTop();
		if ( msg.action == action_t::POP ) {
			if ( Expects( !this->stack.empty() ).Failed() ) {
				continue;
			}
			LOG_INFO( "State pop, id: ", currentStateID.value() );
			this->stack.back()->OnPop();
			this->stack.pop_back();
		} else if ( msg.action == action_t::PUSH ) {
			if ( Expects( !currentStateID.has_value() ||
				 currentStateID.value() != msg.state ).Failed() ) {
				continue;
			}
			LOG_INFO( "State push, id: ", msg.state );
			auto stateToPush = this->createState( msg.state );
			if ( stateToPush.has_value() ) {
				this->stack.push_back( std::move( stateToPush.value() ) );
				this->stack.back()->OnPush();
			}
		}
	}
}

std::optional<stateID> StateStack::GetStateOnTop()
{
	if ( Expects( !this->stack.empty() ).Failed() )
		return {};

	return this->stack.back()->GetID();
}
}