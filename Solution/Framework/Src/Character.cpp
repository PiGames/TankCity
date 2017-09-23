/*
	Untitled_Guys 2017
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Character.hpp"
#include "../Inc/Debug.hpp"

namespace con
{
void Character::Update()
{
	this->Move( this->physicAttributes.velocity * gTime().GetFrameDelta() );

	Pawn::Update();

	auto positionDelta = this->GetPosition() - this->physicAttributes.collider.top;
	this->physicAttributes.collider.top -= positionDelta;
	this->physicAttributes.collider.down -= positionDelta;
}
}