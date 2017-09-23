/*
	Untitled_Guys 2017
*/

namespace con
{
template <typename TActor>
TActor& Scene::Spawn()
{
	static_assert( std::is_base_of_v<Actor, TActor> );

	if ( this->actors.capacity() < this->actors.size() + 1 )
		LOG_WARN( "Scene::actors needs to alloc (now reserved ", this->actors.capacity(), ")" );

	Actor* newActor = nullptr;
	if ( auto freeActor = this->findFreeActor(); freeActor.has_value() ) {
		*freeActor.value() = std::make_unique<TActor>();
		newActor = freeActor.value()->get();
	} else
		newActor = this->actors.emplace_back( std::make_unique<TActor>() ).get();

	if ( Ensures( newActor != nullptr ).Failed() ) {
		gMessenger().Add<exitMessage>( {}, To<int16>( frameworkMessages_t::EXIT ) );
		LOG_ERROR( "Failed to spawn, exit ASAP" );

		static TActor fallbackActor;
		return fallbackActor;
	}

	newActor->_SetUniqueID( ++actorsIDCounter );
	newActor->_SetScene( *this );
	return static_cast<TActor&>( *newActor );
}

}