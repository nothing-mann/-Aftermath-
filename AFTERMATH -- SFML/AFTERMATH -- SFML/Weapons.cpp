#include "stdafx.h"
#include "Weapons.h"

void Weapons::initVariables()
{
	this->range = 500;
	this->damageMin = 1;
	this->damageMax = 3;

	//Timer for the clicks to work..............................
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}



Weapons::Weapons(unsigned level, unsigned value, std::string texture_file)
	:Item(level, value)
{
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULDNOT LOAD WEAPON TEXTURE" << "\n";
	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapons::Weapons(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file)
	:Item(level, value)
{
	this->initVariables();

	this->damageMin = damageMin;
	this->damageMax = damageMax;
	this->range = range;

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

const unsigned Weapons::getDamage() const
{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
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
