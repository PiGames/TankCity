/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

namespace con
{
template<typename TData>
inline void Messenger::Add( const TData& data, int16 id )
{
	auto anyToEmplace = std::make_any<TData>( data );
	this->nextFrameMessages.emplace_back( InternalMessage{ anyToEmplace, id, ++this->uniqueIDCounter } );
}

template<typename TData>
inline std::optional<Messenger::Msg<TData>> Messenger::GetOne( int16 id )
{
	const auto result = std::find_if( this->currentFrameMessages.begin(), this->currentFrameMessages.end(),
									  [id]( auto& msg ) {
		return msg.id == id;
	} );

	if ( result != this->currentFrameMessages.end() ) {
		try {
			auto& casted = std::any_cast<TData&>( result->data );
			return Messenger::Msg<TData>{ casted, id, result->uniqueID };
		} catch ( const std::bad_any_cast& ) {
			LOG_ERROR( "Bad any cast for id ", id, ", ", __FILE__, ": ", __LINE__ );
		}
	}

	return {};
}

template<typename TData>
inline std::vector<Messenger::Msg<TData>> Messenger::GetAll( int16 id )
{
	std::vector<Msg<TData>> tempVec;

	for ( auto& msg : this->currentFrameMessages ) {
		if ( msg.id == id ) {
			TData* toEmplace = nullptr;
			try {
				toEmplace = std::any_cast<TData>( &msg.data );
			} catch ( const std::bad_any_cast& ) {
				LOG_ERROR( "Bad any cast for id ", id, ", ", __FILE__, ": ", __LINE__ );
				continue;
			}
			tempVec.emplace_back( Msg<TData>{ *toEmplace, id, msg.uniqueID } );
		}
	}

	return tempVec;
}

inline void Messenger::SwapBuffers()
{
	this->currentFrameMessages.clear();
	this->currentFrameMessages = this->nextFrameMessages;
	this->nextFrameMessages.clear();
}
}
