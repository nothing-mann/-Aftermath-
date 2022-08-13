#include "stdafx.h"
#include "Rbow.h"



Rbow::Rbow(unsigned value, std::string texture_file)
	:RangedWeapon(value, texture_file)
{
}

Rbow::~Rbow()
{
}

Rbow* Rbow::clone()
{
	return new Rbow(*this);
}

void Rbow::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
}

void Rbow::render(sf::RenderTarget& target, sf::Shader* shader)
{
}
