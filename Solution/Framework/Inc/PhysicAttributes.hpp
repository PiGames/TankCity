/*
	Untitled_Guys 2017
*/

#pragma once

#include "Vec2.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace con
{

struct RectCollider final
{
	// `top` is relative to Characters `position`, `down` is relative to top
	point top, down;

	template <typename T>
	RectCollider( const sf::Rect<T>& sfRect );
	RectCollider() = default;
};

using kilograms = float32;

struct PhysicAttributes final
{
	// TODO: use mass for gravity calculations or remove it?
	kilograms mass = 1;
	RectCollider collider;
	Vec2f velocity;
};

}

#include "../Src/PhysicAttributes.inl"