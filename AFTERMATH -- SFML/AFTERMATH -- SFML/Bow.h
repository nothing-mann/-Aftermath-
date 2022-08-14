#pragma once
#include "Weapon.h"
class Bow :
    public Weapon
{
public:
    Bow(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file);
    virtual ~Bow();

    virtual Bow* clone();

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

