#pragma once
#include "Weapon.h"
class Bow :
    public Weapon
{
public:
    Bow();
    virtual ~Bow();


    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

