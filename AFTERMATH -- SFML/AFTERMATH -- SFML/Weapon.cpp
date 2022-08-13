#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(unsigned value, std::string texture_file)
	:Weapons(value, texture_file)
{
	this->type = ItemTypes::WEAPON;
}

Weapon::~Weapon()
{
}
