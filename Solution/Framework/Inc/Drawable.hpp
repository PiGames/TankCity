/*
	Untitled_Guys 2017
	https://github.com/UntitledGuys/
*/

#pragma once

#include <variant>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Types.hpp"

namespace con
{
namespace priv
{
using drawablePlain = std::variant<sf::Sprite, sf::Text, sf::RectangleShape, sf::CircleShape>;
using drawableVariant = std::variant<sf::Sprite, sf::Text, sf::RectangleShape, sf::CircleShape, std::vector<priv::drawablePlain>>;
}

class Drawable final
{
public:
	int8 GetLayer() const;
	priv::drawableVariant& GetVariantRef();

	void SetLayer( int8 layer_ );

	void _Draw( sf::RenderTarget& target );

private:
	int8 layer = 0;
	priv::drawableVariant toDraw;
};
}