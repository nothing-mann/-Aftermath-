#pragma once
class AttributeComponent
{

public:
	//Levelling
	int level;
	int exp;
	int expNext;
	int attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;


	//Construc/Destruc
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;
	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

