#pragma once
class AttributeComponent
{

public:
	//Levelling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

	//Attributes
	unsigned strength;
	unsigned vitality;
	unsigned dexterity;
	unsigned agility;
	unsigned intelligence;

	//Stats

	//Construc/Destruc
	AttributeComponent();
	virtual ~AttributeComponent();

	//Functions
};

