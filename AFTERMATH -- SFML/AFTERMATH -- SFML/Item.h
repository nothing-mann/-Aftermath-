#pragma once

enum ItemTypes {IT_DEFAULT = 0, RANGEDWEAPON, WEAPON};
enum ItemRarities {COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC};

class Item
{
private:
	void initVariables();
protected:
	//Variables
	short unsigned type;
	unsigned level;
	unsigned value;

public:


	Item(unsigned level, unsigned value);
	virtual ~Item();

	//Function
	virtual Item* clone() = 0;
};

