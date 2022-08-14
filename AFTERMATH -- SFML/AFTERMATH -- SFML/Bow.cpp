#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file)
	:Weapon(level, damageMin, damageMax, range, value, texture_file)
{
	//Visual Weapon


	/*this->weapon_sprite.setOrigin
	(
		this->weapon_sprite.getGlobalBounds().width/2.f,
		this->weapon_sprite.getGlobalBounds().height/2.f
	);*/
}

Bow::~Bow()
{
}

Bow* Bow::clone()
{
	return new Bow(*this);
}

void Bow::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
	//Update visual weapon
	this->weapon_sprite.setPosition(center);

	float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180 / PI;

	this->weapon_sprite.setRotation(deg - 30);

	if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax)
	{
		this->weapon_sprite.move(500.f, 0.f);
	}
}

void Bow::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
		target.draw(this->weapon_sprite, shader);
	else
		target.draw(this->weapon_sprite);
}



