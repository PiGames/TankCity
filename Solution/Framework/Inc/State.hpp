/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Types.hpp"
#include "Scene.hpp"

#include <thread>
#include <atomic>
#include <optional>

namespace con
{
/*	Virtual State class. You can make loading screen with it. You must overwrite
	stateID GetID. You may also override OnPush, OnPop and Update().
*/
class State
{
public:
	State() = default;
	virtual ~State();

	State( const State& ) = delete;
	const State& operator=( const State& ) = delete;

	std::optional<Scene*> GetScene();
	virtual stateID GetID() const = 0;
	virtual void OnPush() {}
	virtual void OnPop() {}
	/* Called every frame - even if State is not on top.
	*/
	virtual void Update();
	virtual void UpdateThread() {}

	void Draw( sf::RenderTarget& target );

	/* Call it when you need to load resources and you don't want to freeze window
		Don't forget to call StopThread()
	*/
	void StartThread();
	void StopThread();

	template <typename TScene>
	TScene& ChangeScene();

protected:
	/* You may want to use it to update only when this state is currently active.
		For example: you probably don't want to update game AI, mobs etc. when Pause state is on top.
	*/
	bool imStateOnTopOfTheStack();
	std::optional<stateID> getStateOnTopOfTheStack();

private:
	std::thread thread;
	std::atomic_bool threadIsRunning = false;
	std::unique_ptr<Scene> scene;

	void threadLoop();
};
}

#include "../Src/State.inl"