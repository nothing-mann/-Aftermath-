#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Variables
    bool jumping; //Convert the jumping into attacking once it is done

    //Initializer functions
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
    void updateJump();
    void updateAnimation(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

