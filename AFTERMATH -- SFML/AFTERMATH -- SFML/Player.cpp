#include "stdafx.h"
#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->jumping = false;
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
	this->createMovementComponent(200.f, 1500.f, 500.f);
	this->createAnimationComponent( texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 3, 0, 48, 48);
	this->animationComponent->addAnimation("JUMP", 10.f, 0, 2, 3, 2, 48, 48);
	this->animationComponent->addAnimation("RUN", 1.5f, 0, 4, 5, 4, 48, 48);
	this->animationComponent->addAnimation("WALK", 10.f, 0, 8, 5, 8, 48, 48);

}

Player::~Player()
{

}


//Accesors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}




//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;
	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;
	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;
	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}


void Player::updateJump() //Change it to attack once it is done
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->jumping = true;

	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->jumping)
	{
		//Set origin depending on direction
		if (this->sprite.getScale().x > 0.f) //Facing right
		{
			this->sprite.setOrigin(0.f, -4.f);
		}
		else //Facing left
		{
			this->sprite.setOrigin(30.f, -4.f);
		}
		//Animate and check for animation and
		if (this->animationComponent->play("JUMP", dt, true)) //When attacking feature is added set the priority animation true to the attack animation
		{
			this->jumping = false;

			if (this->sprite.getScale().x > 0.f) //Facing right
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else //Facing left
			{
				this->sprite.setOrigin(30.f, 0.f);
			}
		}
		//if (this->animationComponent->isDone("JUMP"))

	}
	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(30.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

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
}
void Player::update(const float& dt)
{
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	//	this->attributeComponent->gainExp(20);
	////this->attributeComponent->update();
	//system("cls");
	//std::cout << this->attributeComponent->debugPrint() << "\n";

	this->movementComponent->update(dt);

	this->updateJump();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
