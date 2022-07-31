#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"

//Entity will be the base class for any type of characters we have
class Entity
{
private:
	void initvariables();

protected:
	sf::Texture* texture; // We will not create individual for all the components because loading texture takes a lot of space and time too
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target) ;
};

