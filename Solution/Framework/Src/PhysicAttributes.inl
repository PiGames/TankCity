/*
	Untitled_Guys 2017
*/

namespace con
{

template <typename T>
inline RectCollider::RectCollider( const sf::Rect<T>& sfRect ) :
	top( To<float32>( sfRect.left ), To<float32>( sfRect.top ) ),
	down( To<float32>( sfRect.left + sfRect.width ), To<float32>( sfRect.top + sfRect.height ) )
{}

}