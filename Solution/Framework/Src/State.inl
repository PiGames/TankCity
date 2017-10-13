/*
	Untitled_Guys 2017
*/

#pragma once

namespace con
{
template<typename TScene>
inline TScene& State::ChangeScene()
{
	static_assert( std::is_base_of<Scene, TScene> );
	this->scene = std::make_unique<TScene>();
	return *this->scene;
}
}
