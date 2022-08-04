#include "stdafx.h"
#include "Player.h"
//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{

}
//Constructors Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 2.f, 18.f, 24.f, 30.f);
	this->createMovementComponent(200.f, 15.f, 5.f);
	this->createAnimationComponent( texture_sheet);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 3, 0, 48, 48);
	this->animationComponent->addAnimation("JUMP", 10.f, 0, 2, 3, 2, 48, 48);
	this->animationComponent->addAnimation("RUN", 1.5f, 0, 4, 5, 4, 48, 48);
	this->animationComponent->addAnimation("WALK", 10.f, 0, 8, 5, 8, 48, 48);

}

Player::~Player()
{

}


//Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(30.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	this->hitboxComponent->update();
}
