/*
	Untitled_Guys 2017
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Pawn.hpp"
#include "../Inc/Debug.hpp"
#include "../Inc/Guideline.hpp"

namespace con
{

Pawn::~Pawn()
{
	if ( Expects( this->controller->owner == this ).Failed() )
		return;

	this->controller->owner = nullptr;
}

void Pawn::Update()
{
	Actor::Update();

	if ( this->controller )
		this->controller->Update();
}

Pawn* PawnController::GetPawn()
{
	return this->owner;
}

bool PawnController::HasPawn() const
{
	return this->owner != nullptr;
}

}