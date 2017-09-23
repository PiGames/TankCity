/*
	Untitled_Guys 2017
*/

#pragma once

#include "Pawn.hpp"
#include "PhysicAttributes.hpp"

namespace con
{
class Character :
	public Pawn
{
public:
	Character( const Character& ) = default;
	Character( Character&& ) = default;
	Character& operator=( const Character& ) = default;
	Character& operator=( Character&& ) = default;
	Character() = default;

	virtual ~Character() = default;

	virtual void Update() override;

private:
	PhysicAttributes physicAttributes;
};
}