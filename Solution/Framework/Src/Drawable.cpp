/*
	Untitled_Guys 2017
	https://github.com/UntitledGuys/
*/

#include "../Inc/PCH.hpp"
#include "../Inc/Drawable.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace con
{
int8 Drawable::GetLayer() const
{
	return this->layer;
}

drawableVariant& Drawable::GetVariantRef()
{
	return this->toDraw;
}

sf::Sprite& Drawable::Sprite()
{
	try {
		return std::get<sf::Sprite>( this->toDraw );
	} catch ( const std::bad_variant_access& ) {
		this->toDraw = sf::Sprite();
		return this->Sprite();
	}
}

sf::Text& Drawable::Text()
{
	try {
		return std::get<sf::Text>( this->toDraw );
	} catch ( const std::bad_variant_access& ) {
		this->toDraw = sf::Text();
		return this->Text();
	}
}

sf::RectangleShape& Drawable::RectangleShape()
{
	try {
		return std::get<sf::RectangleShape>( this->toDraw );
	} catch ( const std::bad_variant_access& ) {
		this->toDraw = sf::RectangleShape();
		return this->RectangleShape();
	}}

sf::CircleShape& Drawable::CircleShape()
{
	try {
		return std::get<sf::CircleShape>( this->toDraw );
	} catch ( const std::bad_variant_access& ) {
		this->toDraw = sf::CircleShape();
		return this->CircleShape();
	}}

drawableVec& Drawable::DrawableVec()
{
	try {
		return std::get<drawableVec>( this->toDraw );
	} catch ( const std::bad_variant_access& ) {
		this->toDraw = drawableVec();
		return this->DrawableVec();
	}}

void Drawable::SetLayer( int8 layer_ )
{
	this->layer = layer_;
}

void Drawable::_Draw( sf::RenderTarget& target )
{
	auto drawPlain = [&target]( auto& drawable ) {
		target.draw( drawable );
	};

	auto drawLambda = [&]( auto& drawable ) {
		using arg_t = std::decay_t<decltype( drawable )>;
		if constexpr ( std::is_same_v<arg_t, std::vector<priv::drawablePlain>> )
			for ( auto& drawableVariant : drawable )
				std::visit( drawPlain, drawableVariant );
		else
			drawPlain( drawable );
	};

	std::visit( drawLambda, this->toDraw );
}

}