#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);
	this->backgroundTexture.loadFromFile("Resources/Images/Background/bg1.png");

		this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	this->font.loadFromFile("Fonts/Pixellettersfull.ttf");
	//{
	//	throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");//throw() -- Exits a program and tells us what happened (Error message is displayed)
	//}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");
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

void MainMenuState::initButtons()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->buttons["GAME_STATE"] = new gui::Button(gui::p2pX(36.97f, vm), gui::p2pY(23.14f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), &this->font, "NEW GAME", gui::calcCharSize(vm), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200), sf::Color(184, 134, 11, 255), sf::Color(218, 165, 32, 255), sf::Color(184, 134, 11, 200));
	this->buttons["EDITOR_STATE"] = new gui::Button(gui::p2pX(36.97f, vm), gui::p2pY(46.29f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), &this->font, "EDITOR STATE", gui::calcCharSize(vm), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200), sf::Color(184, 134, 11, 255), sf::Color(218, 165, 32, 255), sf::Color(184, 134, 11, 200));
	this->buttons["SETTINGS_STATE"] = new gui::Button(gui::p2pX(36.97f, vm), gui::p2pY(60.18f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), &this->font, "SETTINGS", gui::calcCharSize(vm), sf::Color(255, 255, 255, 230), sf::Color(255, 255, 255, 230), sf::Color(255, 255, 255, 200), sf::Color(184, 134, 11, 230), sf::Color(218, 165, 32, 230), sf::Color(184, 134, 11, 200));
	this->buttons["EXIT_STATE"] = new gui::Button(gui::p2pX(36.97f, vm), gui::p2pY(83.33f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), &this->font, "QUIT", gui::calcCharSize(vm), sf::Color(0, 0, 0, 230), sf::Color(0, 0, 0, 230), sf::Color(0, 0, 0, 200), sf::Color(70, 70, 70, 230), sf::Color(150, 150, 150, 230), sf::Color(20, 20, 20, 200));

}

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();


}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}




void MainMenuState::updateInput(const float& dt)
{

	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))

}

void MainMenuState::updateButtons()
{
	//Updates all the buttons in the statte and handles thei functionality
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}
	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}
	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	system("cls");
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";

	this->updateButtons();
	
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderButtons(*target);
	
	//Remove Later -- Used for mouse position 
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y-50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(20);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}

