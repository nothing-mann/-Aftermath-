#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizef, sf::Texture& texture, const sf::IntRect& tex_rect)
{
	this->shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(x, y);
	this->shape.setTexture(&texture);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(tex_rect);
}

Tile::Tile()
{
}

Tile::~Tile()
{
}


//Function
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
