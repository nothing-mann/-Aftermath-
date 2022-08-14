#include "stdafx.h"
#include "GameState.h"



void GameState::initDeferredRender()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 
			0, 
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height)
	);


}


void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);
	this->view.setCenter(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width/2.f,
			this->stateData->gfxSettings->resolution.height/2.f
		)
	);
}

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

	this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/player1.png");
	this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png");
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(20.f, 20.f, this->textures["PLAYER_IDLE"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");
	//this->tileMap->loadFromFile("text.ammp");
	this->tileMap = new TileMap("text.ammp");
}

void GameState::initSystems()
{
	this->tts = new TextTagSystem("Fonts/Roboto-Medium.ttf");
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initPlayers();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap();
	this->initSystems();

}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
	delete this->enemySystem;
	delete this->tts;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}


void GameState::updateView(const float& dt)
{


	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width/2)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
	);


	if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) /static_cast<int> (this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int> (this->stateData->gridSize);

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
	{
		this->player->move(0.f, -1.f, dt);
		//if(this->getKeytime())
			//this->player->gainEXP(10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
		//if(this->getKeytime())
			//this->player->loseEXP(10);
	}
	
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);

	this->tileMap->update(this->player, dt);


}

void GameState::updatePlayer(const float& dt)
{
}

void GameState::updateCombatAndEnemies(const float& dt)
{
	unsigned index = 0;
	for (auto* enemy : this->activeEnemies)
	{
		enemy->update(dt, this->mousePosView);

		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);

		this->updateCombat(enemy,index, dt);

		//Dangerous
		if (enemy->isDead())
		{
			this->player->gainEXP(enemy->getGainExp());
			this->tts->addTextTag(EXPERIENCE_TAG, this->player->getCenter().x, this->player->getCenter().y, static_cast<int>(enemy->getGainExp()));
			this->activeEnemies.erase(this->activeEnemies.begin() + index);

 			--index;
		}

		++index;
	}

}

void GameState::updateCombat(Enemy* enemy, const int index,const float& dt)
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->player->getWeapon()->getAttackTimer()
			&& enemy->getGlobalBounds().contains(this->mousePosView) && /*std::abs(this->player->getPosition().x - i->getPosition().x) <= this->player->getWeapon()->getRange()*/ enemy->getDistance(*this->player) < this->player->getWeapon() ->getRange() )          //This lets us do the shooting basically. here we get the distance between the player and the enemy and when within the range kills															the enemy if hit on the area where the enemy is (here, the range is 500.f)
		{
			//Get to this!!
			std::cout << "Hit" << "\n";
			int dmg = static_cast<int>(this->player->getWeapon()->getDamage());
			enemy->loseHP(dmg);
			this->tts->addTextTag(NEGATIVE_TAG, enemy->getPosition().x, enemy->getPosition().y, dmg);
				
		}
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this -> paused) // Unpaused update
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->updateTileMap(dt);

		this->player->update(dt, this->mousePosView);

		this->playerGUI->update(dt);

		//Update all enemies
		this->updateCombatAndEnemies(dt);

		//Update Systems
		this->tts->update(dt);
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(
		this->renderTexture, 
		this->viewGridPosition,
		&this->core_shader,
		this->player->getCenter(),
		false);

	for (auto* enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}

	this->player->render(this->renderTexture, &this->core_shader , this->player->getCenter(), false);

	

	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());

	this->tts->render(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) //Paused menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//Final Render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
