#include "Game.h"

//Static Fuctions

//Initializer functions


void Game::initvariables()
{
    this->window = nullptr;
    this->fullscreen = false;
    this->dt = 0.f;
}

void Game::initwindow()
{
	//Creates SFML window using window.ini file

    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds=sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }
    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    
    if(this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen , windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title,  sf::Style::Titlebar | sf::Style::Close, windowSettings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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
void Game::initstates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));

}



//Constructors and destructors
Game::Game()
{
    //All the initializations should be declared here too
    this->initwindow();
    this->initkeys();
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
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
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

