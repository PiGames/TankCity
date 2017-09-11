/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "PCH.hpp"
#include "Misc.hpp"
#include "Debug.hpp"
#include "Single.hpp"

#include <any>
#include <optional>

namespace con
{
/* Handles messaging between everything in Game.
*/
class Messenger final :
	public Single<Messenger>
{
public:
	template <typename TData>
	struct Msg	// Templated version of InternalMessage structure.
	{
		TData& data;
		int16 id;
		uint32 uniqueID;
		//	Msg( TData& data_, int16 id_, uint32 uniqueID_ );
	};
	/* Adds message to messenger. Will be avaible to read in next frame.
		Data is copied. One id must have one data type.
	*/
	template <typename TData>
	void Add( const TData& data, int16 id );
	/* Returns message of given id. Nullptr if cannot find or bad any cast
		was thrown.
	*/
	template <typename TData>
	std::optional<Msg<TData>> GetOne( int16 id );
	/* Returns vector of pointers to messages of given id. Empty if cannot find
		any. Skip if bad any cast was thrown.
	*/
	template <typename TData>
	std::vector<Msg<TData>> GetAll( int16 id );

	/* Swaps pending messages (added in current frame) with this that can be
		accesed in current frame. Cleans pending message storage.
	*/
	void SwapBuffers();

private:
	struct InternalMessage final
	{
		std::any data;
		int16 id;
		uint32 uniqueID;
		//	InternalMessage( std::any& data_, int16 id_, uint32 uniqueID_ );
	};
	using buffer_t = std::vector<InternalMessage>;

	uint32 uniqueIDCounter = 0;
	buffer_t nextFrameMessages;
	buffer_t currentFrameMessages;
};
}

#include "../Src/Messaging.inl"