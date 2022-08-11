#include "stdafx.h"
#include "SettingsState.h"


//Initializer functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}


void SettingsState::initFonts()
{
	this->font.loadFromFile("Fonts/Pixellettersfull.ttf");
	//{
	//	throw("ERROR::SettingsSTATE::COULD NOT LOAD FONT");//throw() -- Exits a program and tells us what happened (Error message is displayed)
	//}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/settingsstate_keybinds.ini");
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

void SettingsState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->backgroundTexture.loadFromFile("Resources/Images/Background/bg1.png");

	this->background.setTexture(&this->backgroundTexture);


	//Buttons
	this->buttons["BACK"] = new gui::Button(gui::p2pX(72.91f, vm), gui::p2pY(83.33f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), &this->font, "BACK", gui::calcCharSize(vm), sf::Color(0, 0, 0, 230), sf::Color(0, 0, 0, 230), sf::Color(0, 0, 0, 200), sf::Color(70, 70, 70, 230), sf::Color(150, 150, 150, 230), sf::Color(20, 20, 20, 200));
	this->buttons["APPLY"] = new gui::Button(gui::p2pX(72.91f, vm), gui::p2pY(74.07f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), &this->font, "APPLY", gui::calcCharSize(vm), sf::Color(0, 0, 0, 230), sf::Color(0, 0, 0, 230), sf::Color(0, 0, 0, 200), sf::Color(184, 134, 11, 230), sf::Color(218, 165, 32, 230), sf::Color(184, 134, 11, 200));


	//Modes
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	
	//DropDownLists
	this->dropDownLists["RESOLUTION"] = new gui::DropDownBox(gui::p2pX(42.f, vm), gui::p2pY(42.f, vm), gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm), font, modes_str.data(), modes_str.size());


	//Text init
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(31.25f, vm),gui::p2pY(41.7f, vm)));

	this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString("Resolution \n\nFullscreen \nAntialiasing \nVsync");
}

void SettingsState::resetGui()
{
	/*
	* Clears the Gui elements and reinitializes the GUI.
	* @return void
	*/
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();
	
	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
}


SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

//Functions

void SettingsState::updateInput(const float& dt)
{

	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))

}

void SettingsState::updateGui(const float& dt)
{
	//Updates all the buttons in the statte and handles thei functionality
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	//Button functionality

	//Settings


	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//Remove later
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution,this->stateData->gfxSettings->title, sf::Style::Default);
		
		this->resetGui();
	}
	//Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}
	//Dropdownlists functionality
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	system("cls");
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";

	this->updateGui(dt);


}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderGui(*target);

	target->draw(this->optionsText);
	//Remove Later -- Used for mouse position 
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(20);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}

