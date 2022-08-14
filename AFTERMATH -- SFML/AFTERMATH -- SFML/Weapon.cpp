#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file)
	:Weapons(level, damageMin, damageMax, range, value, texture_file)
{
	this->type = ItemTypes::WEAPON;
}

Weapon::~Weapon()
{
}

void Weapon::generate(const unsigned levelMin, const unsigned levelMax)
{
	this->level = rand() % (levelMax - levelMin + 1) + levelMin;
	this->damageMin = this->level * (rand() % 2 + 1);
	this->damageMax = this->level * (rand() % 2 + 1) + this->damageMin;

	this->range = this->level + rand() % 10 + 400;

	this->value = this->level + this->damageMin + this->damageMax + this->range + (rand() % level * 10);

	std::cout << this->level << " " << this->damageMin << " " << this->damageMax << " " << this->range << " " << this->value << "\n";
}
