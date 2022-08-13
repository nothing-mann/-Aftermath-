#include "stdafx.h"
#include "Weapons.h"

void Weapons::initVariables()
{
	this->range = 20;
	this->damageMin = 1;
	this->damageMax = 2;

	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
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

const unsigned& Weapons::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapons::getDamageMax() const
{
	return this->damageMax;
}


//Accessors
const unsigned& Weapons::getRange() const
{
	return this->range;
}

const bool Weapons::getAttackTimer()
{
	std::cout << this->attackTimer.getElapsedTime().asMilliseconds() << "\n";
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}
