/*
	Untitled_Guys 2017
	https://github.com/UntitledGuys/
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Pawn.hpp"
#include "../Inc/Debug.hpp"
#include "../Inc/Guideline.hpp"

namespace con
{

PawnController* Pawn::GetController()
{
	return this->controller.get();
}

void Pawn::Update()
{
	Actor::Update();

	if ( this->controller )
		this->controller->Update();
}

Pawn* PawnController::GetOwner()
{
	return this->owner;
}

bool PawnController::HasOwner() const
{
	return this->owner != nullptr;
}

void PawnController::posses( Pawn* owner_ )
{
	this->owner = owner_;
}

}