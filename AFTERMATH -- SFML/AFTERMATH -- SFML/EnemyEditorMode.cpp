#include "stdafx.h"
#include "EnemyEditorMode.h"



//Initializer Functions
void EnemyEditorMode::initVariables()
{
	type = 0;
	amount = 1;
	timeToSpawn = 60;  //in seconds
	maxDistance = 1000.f;
}


void EnemyEditorMode::initGui()
{
	//Text
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(20);
	this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);


	//General Gui

	this->sidebar.setSize(sf::Vector2f(60.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);
}


//Constructors destructors
EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	:EditorMode(state_data, tile_map, editor_state_data)
{
	this->initVariables();
	this->initGui();
}

EnemyEditorMode::~EnemyEditorMode()
{
	
}

void EnemyEditorMode::updateInput(const float& dt)
{
	//Adds a tile to tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{

			this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect,
			this->type, this->amount, this->timeToSpawn, this->maxDistance);

		}

	}
	//Removes a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			//if(this->tileMap->checkType(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::ENEMYSPAWNER))
				this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::ENEMYSPAWNER);
		}
	}

	//Toggle Collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (this->type > 0)
				this->type--;
		}
		else if (this->type < 1000)
			this->type++;
		else
			this->type = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("AMOUNT_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (this->amount > 0)
				this->amount--;
		}
		else if (this->amount < 1000)
			this->amount++;
		else
			this->amount = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TTS_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (this->timeToSpawn > 0)
				this->timeToSpawn--;
		}
		else if (this->timeToSpawn < 1000)
			this->timeToSpawn++;
		else
			this->timeToSpawn = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("MD_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (this->maxDistance > 0)
				this->maxDistance--;
		}
		else if (this->maxDistance < 1000)
			this->maxDistance++;
		else
			this->maxDistance = 0;
	}

}

void EnemyEditorMode::updateGui(const float& dt)
{
	this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);

	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 50.f);

	std::stringstream ss;
	ss << /*this->editorStateData->mousePosView->x << " " << this->editorStateData->mousePosView->y << "\n" << this->editorStateData->mousePosGrid->x << " " << this->editorStateData->mousePosGrid->y << "\n" << this->textureRect.left << " " << this->textureRect.top <<*/ 
		"\n" << "Enemy Type: " << this->type <<
		"\n" << "Enemy Amount: " << this->amount <<
		"\n" << "Time to spawn: " << this->timeToSpawn <<
		"\n" << "Max Distance: " << this->maxDistance;
	this->cursorText.setString(ss.str());
}

void EnemyEditorMode::update(const float& dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target)
{
	target.setView(*this->editorStateData->view);
	target.draw(this->selectorRect);
	target.draw(this->cursorText);

	target.setView(target.getDefaultView());
	target.draw(this->sidebar);
}

void EnemyEditorMode::render(sf::RenderTarget& target)
{
	this->renderGui(target);
}
