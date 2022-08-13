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

    int damageMin;
    int damageMax;
    unsigned range;

public:
    Weapons(unsigned value, std::string texture_file);
    virtual ~Weapons();

    //Accessors
    const unsigned& getRange() const;

    //Function
    virtual Item* clone() = 0;
    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;

};

