#pragma once

class Tile
{
private:
protected:
	sf::RectangleShape shape;
public:
	Tile();
	Tile(float x, float y, float gridSizef);
	virtual ~Tile();
	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

