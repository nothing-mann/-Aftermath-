#pragma once
#include "Tile.h"

class EnemySpawnerTile
	:public Tile
{
private:
	int enemyType;
	int enemyAmount;
	int enemyCounter;
	sf::Clock enemySpawnTimer;
	sf::Int32 enemyTimeToSpawn;
	float enemyMaxDistance;

	bool spawned;

	//Spawn timer


public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizef,
		sf::Texture& texture, const sf::IntRect& tex_rect, 
		 int enemy_type, 
		int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawnerTile();

	//Accessors
	virtual const std::string getAsString() const;
	const bool& getSpawned() const;
	const int& getEnemyAmount() const;
	const int& getEnemyCounter() const;

	//Modifiers
	void setSpawned(const bool spawned);
	const bool canSpawn() const;
	
	//Functions
	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

