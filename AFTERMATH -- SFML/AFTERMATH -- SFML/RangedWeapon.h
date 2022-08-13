#pragma once

#include "Weapons.h"

class RangedWeapon :
    public Weapons
{
private:

protected:

public:
    RangedWeapon(unsigned value, std::string texture_file);
    virtual ~RangedWeapon();
    
    virtual RangedWeapon* clone() = 0;

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;

};

