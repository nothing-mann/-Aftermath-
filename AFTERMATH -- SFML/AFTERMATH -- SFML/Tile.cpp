#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizef, sf::Texture& texture, const sf::IntRect& tex_rect, bool collision, short type)
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




//Functions
const bool& Tile::getCollision() const
{
	return this->collision;
}
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

const std::string Tile::getAsString() const
{
	std::stringstream ss;
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
	return ss.str();
}

void Tile::update()
{

}


void Tile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);
		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}
