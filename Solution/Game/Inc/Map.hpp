#pragma once
#include "Types.hpp"
#include "Logger.hpp"
#include "Guideline.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Vertex.hpp>


using namespace con;

struct Cell
{
	sf::Vector2i position;
	uint16 id;

	Cell() = default;
	Cell( uint16 id_, sf::Vector2u position_ ) :
		id(id_), position(position_)
	{
	}
};

class Map
{
	const sf::Vector2u tileSize = { 64u, 64u };
public:
	Map() {}

	bool LoadFromFile( const std::string& path );
	void UpdateTilesVerticies();
	void Draw( sf::RenderTarget& target, sf::RenderStates states );

	Cell* GetCell( int16 x, int16 y );

	std::vector<Cell*> GetTiles();
	uint16 getVersion();
	sf::Texture* getTileSet();

private:
	sf::Vector2u size;
	uint16 version;
	sf::Texture tileSet;
	std::vector<Cell> tiles;
	sf::VertexArray vertices;
};

