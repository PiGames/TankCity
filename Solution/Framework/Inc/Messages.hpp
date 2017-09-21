/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Types.hpp"

#include <SFML/Window/Event.hpp>

namespace std
{
template <typename T>
class optional;
}

namespace con
{
enum class frameworkMessages_t : int16
{
	STATE_PUSH,
	STATE_POP,
	STATE_GET_ON_TOP, // sent every update.
	INPUT,
	EXIT
};

struct empty_t final // cannot use void 
{};

using statePushMessage_t = stateID;
using statePopMessage_t = empty_t;
using stateGetOnTopMessage_t = std::optional<stateID>;
using inputMessage_t = sf::Event;
using exitMessage_t = empty_t;
}