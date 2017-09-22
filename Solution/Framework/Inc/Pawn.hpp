/*
	Untitled_Guys 2017
*/

#pragma once

#include "Actor.hpp"

namespace con
{
class PawnController;

class Pawn :
	public Actor
{
public:
	Pawn( const Pawn& ) = default;
	Pawn( Pawn&& ) = default;
	Pawn& operator=( const Pawn& ) = default;
	Pawn& operator=( Pawn&& ) = default;
	Pawn() = default;

	virtual ~Pawn() = default;

	PawnController* GetController();

	template <typename TPawnController>
	TPawnController* ResetController();

	virtual void Update() override;

private:
	std::unique_ptr<PawnController> controller;
};

class PawnController
{
	friend class Pawn;

public:
	PawnController( const PawnController& ) = default;
	PawnController( PawnController&& ) = default;
	PawnController& operator=( const PawnController& ) = default;
	PawnController& operator=( PawnController&& ) = default;
	PawnController() = default;

	virtual ~PawnController() = default;

	Pawn* GetOwner();

	bool HasOwner() const;

	virtual void Update() = 0;

private:
	Pawn* owner = nullptr;

	void posses( Pawn* owner_ );
};
}

#include "../Src/Pawn.inl"