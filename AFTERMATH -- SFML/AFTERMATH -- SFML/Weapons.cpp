#include "stdafx.h"
#include "Weapons.h"

void Weapons::initVariables()
{
	this->range = 20;
}

Weapons::Weapons(unsigned value, std::string texture_file)
	:Item(value)
{
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULDNOT LOAD WEAPON TEXTURE" << "\n";
	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapons::~Weapons()
{
}


//Accessors
const unsigned& Weapons::getRange() const
{
	return this->range;
}
