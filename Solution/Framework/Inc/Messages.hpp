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

struct empty final // cannot use void 
{};

using statePushMessage = stateID;
using statePopMessage = empty;
using stateGetOnTopMessage = std::optional<stateID>;
using inputMessage = sf::Event;
using exitMessage = empty;
}