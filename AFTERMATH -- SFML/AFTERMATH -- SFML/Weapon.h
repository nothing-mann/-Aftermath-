#pragma once
#include "Weapons.h"
class Weapon :
    public Weapons
{
private:

protected:
 

public:
    Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file);
    virtual ~Weapon();

    virtual Weapon* clone() = 0;
    virtual void generate(const unsigned levelMin, const unsigned levelMax);

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader) = 0;

};

