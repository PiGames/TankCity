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
		stateID_t state;
		uint32 uniqueID;
	};

public:
	template <typename TState>
	void RegisterState( stateID_t id );

	void Update();
	/* Returns stateID_t of State on top. Nothing if no states on stack.
	*/
	std::optional<stateID_t> GetStateOnTop();

private:
	using StatePtr = std::unique_ptr<State>;

	std::vector<StatePtr> stack;
	std::unordered_map<stateID_t, std::function<StatePtr()>> factories;

	std::optional<StatePtr> createState( stateID_t id );
	using actionMessagesVector_t = std::vector<actionMessage_t>;
	actionMessagesVector_t getOrderedMessages();
	void applyMessages( const actionMessagesVector_t& messages );
};
}

#include "../Src/StateStack.inl"