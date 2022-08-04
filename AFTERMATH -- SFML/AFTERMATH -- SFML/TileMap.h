#pragma once

#include "Tile.h"
class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	sf::Texture tileTextureSheet;
public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;

	void update();
	void render(sf::RenderTarget& target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
};

