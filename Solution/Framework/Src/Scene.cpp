/*
	Untitled_Guys 2017
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Scene.hpp"
#include "../Inc/Guideline.hpp"
#include "../Inc/Debug.hpp"

namespace con
{

Scene::Scene( uint32 reserve )
{
	if constexpr( IS_DEBUG )
		if ( Expects( reserve > 1 ).Failed() )
			return;

	this->actors.reserve( reserve );
}

bool Scene::Kill( int32 actorUniqueID )
{
	auto actor = this->findActorByID( actorUniqueID );
	if ( !actor.has_value() )
		return false;

	actor.value()->reset();

	return false;
}

void Scene::Update()
{
	for ( auto& actor : this->actors )
		if ( actor )
			actor->Update();
}

void Scene::Draw( sf::RenderTarget& target )
{
	this->sortActorsByDrawLayer();
	for ( auto& actor : this->actors )
		if ( actor )
			actor->Draw( target );
}

void Scene::sortActorsByDrawLayer()
{
	std::sort( this->actors.begin(), this->actors.end(),
			   []( auto& a, auto& b ) {
		if ( !a || !b )
			return false;

		auto layerA = a->DrawableRef().GetLayer();
		auto layerB = b->DrawableRef().GetLayer();

		return layerA < layerB;
	} );
}

std::optional<std::unique_ptr<Actor>*> Scene::findActorByID( int32 uniqueID )
{
	auto result = std::find_if( this->actors.begin(), this->actors.end(),
								[uniqueID]( const auto& actor ) {
		return actor && actor->GetUniqueID() == uniqueID;
	} );

	if ( result == this->actors.end() )
		return {};

	if constexpr ( IS_DEBUG )
		if ( Ensures( ( *result ).get() != nullptr ).Failed() )
			return {};

	return &( *result );
}

std::optional<std::unique_ptr<Actor>*> Scene::findFreeActor()
{
	auto result = std::find_if( this->actors.begin(), this->actors.end(),
								[]( const auto& actor ) {
		return !actor;
	} );

	if ( result == this->actors.end() )
		return {};

	return &( *result );
}

}
