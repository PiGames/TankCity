/*
	Untitled_Guys 2017
*/

#pragma once

#include "Actor.hpp"

namespace con
{
class PawnController;

/* It's extended Actor - you can controll it using PawnController.
*/
class Pawn :
	public Actor
{
public:
	Pawn( const Pawn& ) = default;
	Pawn( Pawn&& ) = default;
	Pawn& operator=( const Pawn& ) = default;
	Pawn& operator=( Pawn&& ) = default;
	Pawn() = default;

	virtual ~Pawn();

	template <typename TPawnController>
	void ResetController();

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

	Pawn* GetPawn();
	virtual int32 GetID() const = 0;

	bool HasPawn() const;

	virtual void Update() = 0;

private:
	Pawn* owner = nullptr;
};
}

#include "../Src/Pawn.inl"