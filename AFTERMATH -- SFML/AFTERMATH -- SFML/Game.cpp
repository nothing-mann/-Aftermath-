#include "stdafx.h"
#include "Game.h"

//Static Fuctions

//Initializer functions


void Game::initvariables()
{
    this->window = nullptr;

    this->dt = 0.f;

    this->gridSize = 64.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");


}

void Game::initwindow()
{
	//Creates SFML window

   

    
    if(this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen , this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title,  sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}
void Game::initkeys()
{
    std::ifstream ifs("Config/supported_keys.ini");
    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }
    ifs.close();

//Debug only. Can be removed later
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }

}
void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}
void Game::initstates()
{
    this->states.push(new MainMenuState(&this->stateData));

}



//Constructors and destructors
Game::Game()
{
    //All the initializations should be declared here too
    this->initvariables();
    this->initGraphicsSettings();
    this->initwindow();
    this->initkeys();
    this->initStateData();
    this->initstates();
    
}

Game::~Game()
{
	delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top(); //Removes the data pointer is holding
        this->states.pop(); //Actually removes the pointer
    }
}





//Functions
void Game::endApplication()
{
    std::cout << "Ending Application!" << "\n";
}
void Game::updateDt()
{
    //Updates the dt variable with the time it ttakes to update and render one frame

    this->dt = this->dtClock.restart().asSeconds(); //As seconds because we want small values
}
void Game::updateSFMLEvents()
{
        while (this->window->pollEvent(this->sfEvent))
        {
            if (this->sfEvent.type == sf::Event::Closed)
                this->window->close();
        }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);

            if (this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    //Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();
    //Render Items
    if (!this->states.empty())
        this->states.top()->render(this->window);
    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();//Resets the delta time here
        this->update();
        this->render();
    }
}

