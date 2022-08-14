#pragma once
#include "Enemy.h"
#include "AIFollow.h"
class Rat :
    public Enemy
{
private:
    void initVariables();
    void initAnimations();
    void initGUI();
    void initAI();

    sf::RectangleShape hpBar;

    AIFollow* follow;

public:
    Rat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
    virtual ~Rat();

    //Functions
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);
    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);
};

