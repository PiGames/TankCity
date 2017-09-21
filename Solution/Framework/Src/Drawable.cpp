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

priv::drawableVariant& Drawable::GetVariantRef()
{
	return this->toDraw;
}

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