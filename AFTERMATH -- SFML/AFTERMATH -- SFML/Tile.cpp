#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizef, sf::Texture& texture, const sf::IntRect& tex_rect, bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizef, static_cast<float>(grid_y) * gridSizef);
	this->shape.setTexture(&texture);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(tex_rect);

	this->collision = collision;
	this->type = type;
}


Tile::~Tile()
{
}


//Accessor
const bool& Tile::getCollision() const
{
	return this->collision;
}
const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

//Function
const std::string Tile::getAsString() const
{
	std::stringstream ss;
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
	return ss.str();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
