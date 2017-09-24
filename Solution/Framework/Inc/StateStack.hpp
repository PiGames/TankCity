/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "State.hpp"
#include "Guideline.hpp"

namespace con
{
class StateStack final
{
	enum class action_t : uint8
	{
		PUSH,
		POP
	};

	struct actionMessage_t final
	{
		action_t action;
		stateID state;
		uint32 uniqueID;
	};

public:
	template <typename TState>
	void RegisterState( stateID id );

	void Update();
	/* Returns stateID of State on top. Nothing if no states on stack.
	*/
	std::optional<stateID> GetStateOnTop();

private:
	using StatePtr = std::unique_ptr<State>;

	std::vector<StatePtr> stack;
	std::unordered_map<stateID, std::function<StatePtr()>> factories;

	std::optional<StatePtr> createState( stateID id );
	using actionMessagesVector_t = std::vector<actionMessage_t>;
	actionMessagesVector_t getOrderedMessages();
	void applyMessages( const actionMessagesVector_t& messages );
	void applyPop();
	void applyPush( const actionMessage_t& message );
};
}

#include "../Src/StateStack.inl"