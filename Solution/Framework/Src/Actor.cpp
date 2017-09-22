/*
	Untitled_Guys 2017
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Actor.hpp"
#include "../Inc/Guideline.hpp"

namespace con
{
Actor::Actor( int32 uniqueID_ ) :
	uniqueID( uniqueID_ )
{}

point Actor::GetPosition() const
{
	return this->position;
}

degrees Actor::GetRotation() const
{
	return this->rotation;
}

int32 Actor::GetUniqueID() const
{
	return this->uniqueID;
}

Drawable& Actor::DrawableRef()
{
	return this->toDraw;
}

void Actor::SetPosition( const point& position_ )
{
	this->position = position_;
}

void Actor::SetRotation( degrees rotation_ )
{
	this->rotation = rotation_;
}

void Actor::Rotate( degrees angle )
{
	if ( angle < -360 || angle > 360 )
		angle = convertToCorrectDegrees( angle );

	this->rotation = convertToCorrectDegrees( this->rotation + angle );
}

void Actor::Move( const Vec2f& force )
{
	this->position += force;
}

void Actor::Update()
{

	auto transformPlain = [this]( auto& transformable ) {
		transformable.setRotation( this->rotation );
		transformable.setPosition( this->position.AsSFMLVec() );
	};

	auto transformUpdate = [&]( auto& transformable ) {
		using arg_t = std::decay_t<decltype( transformable )>;
		if constexpr ( std::is_same_v<arg_t, std::vector<priv::drawablePlain>> )
			for ( auto& transformableVariant : transformable )
				std::visit( transformPlain, transformableVariant );
		else
			transformPlain( transformable );
	};

	std::visit( transformUpdate, this->toDraw.GetVariantRef() );
}

void Actor::Draw( sf::RenderTarget& target )
{
	this->toDraw._Draw( target );
}

degrees Actor::convertToCorrectDegrees( degrees in )
{
	while ( in > 360 )
		in -= 360;

	while ( in < 0 )
		in += 360;

	return in;
}

}