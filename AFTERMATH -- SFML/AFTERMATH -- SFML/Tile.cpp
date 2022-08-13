#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(short type, int grid_x, int grid_y, float gridSizef, sf::Texture& texture, const sf::IntRect& tex_rect, const bool collision)
{
	//this->shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	//this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizef, static_cast<float>(grid_y) * gridSizef);
	this->shape.setTexture(texture);
	this->shape.setTexture(texture);
	this->shape.setTextureRect(tex_rect);

	this->collision = collision;
	this->type = type;
}


Tile::~Tile()
{
}



//Accessor
const short& Tile::getType() const
{
	return this->type;
}
const bool& Tile::getCollision() const
{
	return this->collision;
}



//Functions

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}



//Function
const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

