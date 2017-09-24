/*
	Untitled_Guys 2017
*/

#pragma once

#include "Actor.hpp"
#include "Messages.hpp"
#include "Messaging.hpp"

#include <optional>

namespace con
{
class Scene
{
public:
	Scene( const Scene& ) = default;
	Scene( Scene&& ) = default;
	Scene& operator=( const Scene& ) = default;
	Scene& operator=( Scene&& ) = default;
	Scene() = default;
	Scene( uint32 reserve );

	virtual ~Scene() = default;

	virtual int32 GetID() const = 0;

	template <typename TActor>
	TActor& Spawn();
	bool Kill( int32 actorUniqueID );

	virtual void Update();
	void Draw( sf::RenderTarget& target );

private:
	std::vector<std::unique_ptr<Actor>> actors;
	int32 actorsIDCounter = -1;

	void sortActorsByDrawLayer();
	std::optional<std::unique_ptr<Actor>*> findActorByID( int32 uniqueID );
	std::optional<std::unique_ptr<Actor>*> findFreeActor();
};
}

#include "../Src/Scene.inl"