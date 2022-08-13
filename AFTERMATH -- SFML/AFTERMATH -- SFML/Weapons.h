#pragma once
#include "Item.h"
class Weapons :
    public Item
{
private:
    void initVariables();

protected:
    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;

    unsigned damageMin;
    unsigned damageMax;
    unsigned range;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;
public:
    Weapons(unsigned value, std::string texture_file);
    virtual ~Weapons();

    //Accessors
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;

    const unsigned& getRange() const;
    const bool getAttackTimer();

    //Function
    virtual Item* clone() = 0;
    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;

};

