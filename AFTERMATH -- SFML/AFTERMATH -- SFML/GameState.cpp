#include "stdafx.h"
#include "GameState.h"


void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}
void GameState::initFonts()
{
	this->font.loadFromFile("Fonts/Pixellettersfull.ttf");
	//{
	//	throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");//throw() -- Exits a program and tells us what happened (Error message is displayed)
	//}
}

void GameState::initTextures()
{

	this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/Biker.png");
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 800.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pmenu;
	delete this->tileMap;
}


void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpausedState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{

	//Update Player input -- Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move( -1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move( 1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move( 0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move( 0.f, 1.f, dt);
	
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this -> paused) // Unpaused update
	{
		
		this->updatePlayerInput(dt);
		this->player->update(dt);
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//this->map.render(*target);
	this->player->render(*target);
	if (this->paused) //Paused menu render
	{
		this->pmenu->render(*target);
	}
}
