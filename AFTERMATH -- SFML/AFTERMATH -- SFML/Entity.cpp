#include "Entity.h"

Entity::Entity()
{

	this->movementSpeed = 100.f;
}

Entity::~Entity()
{
	delete this->sprite;
}


void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->sprite)
	{ 
		this->sprite->move(dir_x*this->movementSpeed*dt, dir_y*this->movementSpeed*dt);
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}