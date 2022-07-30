#pragma once

#include "MovementComponent.h"

//Entity will be the base class for any type of characters we have
class Entity
{
private:
	void initvariables();

protected:
	sf::Texture* texture; // We will not create individual for all the components because loading texture takes a lot of space and time too
	sf::Sprite* sprite;

	MovementComponent* movementComponent;
public:
	Entity();
	virtual ~Entity();

	//Component functions
	void createSprite(sf::Texture* texture);
	void createMovementComponent(const float maxVelocity);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float dir_x, const float dir_y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target) ;
};

