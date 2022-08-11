#pragma once
#include "Item.h"
class Weapon :
    public Item
{
private:

protected:
    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;

    int damageMin;
    int damageMax;

public:
    Weapon();
    virtual ~Weapon();


    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader) = 0;

};

