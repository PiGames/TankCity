#include "Map.hpp"

#include <iostream>

std::vector<Cell*> Map::GetTiles()
{
	std::vector<Cell*> tilesPtr;
	tilesPtr.reserve( tiles.size() );
	for ( auto& tile : this->tiles ) {
		tilesPtr.push_back( &tile );
	}

	return tilesPtr;
}

sf::Texture* Map::getTileSet()
{
	return &this->tileSet;
}

uint16 Map::getVersion()
{
	return this->version;
}

bool Map::LoadFromFile( const std::string& path )
{
	std::ifstream file( path );
	if ( !file.is_open() )
		return false;

	file >> this->version;

	std::string tileSetPath;
	file >> tileSetPath;
	if ( Expects( this->tileSet.loadFromFile( tileSetPath ) ).Failed() ) {
		return false;
	}

	uint16 width, height;
	file >> width;
	file >> height;
	if ( Expects( width > 0 && height > 0 ).Failed() ) {
		return false;
	}

	this->size = sf::Vector2u( width, height );

	this->tiles.clear();
	this->tiles.reserve( width * height );

	for ( auto i = 0u; i < height; ++i ) {
		for ( auto j = 0u; j < width; ++j ) {
			uint16 id;
			file >> id;
			this->tiles.push_back( Cell( id, { tileSize.x * j, tileSize.y * i } ) );
		}
	}

	if ( Ensures( this->tiles.size() == width * height).Failed() ) {
		this->tiles.clear();
		return false;
	}

	return true;
}

void Map::UpdateTilesVerticies()
{
	uint16 width = this->size.x;
	uint16 height = this->size.y;
	this->vertices.setPrimitiveType( sf::Quads );
	this->vertices.resize( width * height * 4 );

	for ( const auto& cell : this->tiles ) {
		uint16 posX = cell.position.x;
		uint16 posY = cell.position.y;
		auto id = cell.id;
		
		uint16 i = posX / tileSize.x, j = posY / tileSize.y;
		
		sf::Vertex* quad = &this->vertices[( i + j * width ) * 4];

		quad[0].position = sf::Vector2f( ( i + 1 ) * tileSize.x, j * tileSize.y );
		quad[1].position = sf::Vector2f( i * tileSize.x, j * tileSize.y );
		quad[2].position = sf::Vector2f( i * tileSize.x, ( j+ 1 ) * tileSize.y );
		quad[3].position = sf::Vector2f( ( i + 1 ) * tileSize.x, ( j + 1 ) * tileSize.y );

		quad[0].texCoords = sf::Vector2f( id * tileSize.x, 0 );
		quad[1].texCoords = sf::Vector2f( ( id + 1 ) * tileSize.x, 0 );
		quad[2].texCoords = sf::Vector2f( ( id + 1 ) * tileSize.x, tileSize.y );
		quad[3].texCoords = sf::Vector2f( id * tileSize.x, tileSize.y );
	}
}

void Map::Draw( sf::RenderTarget& target, sf::RenderStates states )
{
	/*
	sf::View view = window.getView();
	sf::FloatRect screenRect( sf::Vector2f( view.getCenter().x - ( view.getSize().x ) / 2, view.getCenter().y - ( view.getSize().y ) / 2 ), view.getSize() );

	for ( auto& cell : this->tiles ) {
		sf::FloatRect collider( cell.sprite.getGlobalBounds().left, cell.sprite.getGlobalBounds().top, Map::tileSize.x, Map::tileSize.y );
		if ( screenRect.intersects( collider ) ) {
			window.draw( cell.sprite );
		}
	}
	*/
	//states.transform *= getTransform();
	states.texture = &tileSet;
	target.draw( vertices, states );
}

Cell* Map::GetCell( int16 x, int16 y )
{
	for ( auto& tile : this->tiles )
		if ( tile.position == sf::Vector2i{ x, y } )
			return &tile;
}
