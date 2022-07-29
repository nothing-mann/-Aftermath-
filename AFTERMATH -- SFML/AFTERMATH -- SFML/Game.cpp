#include "Game.h"

//Static Fuctions

//Initializer functions


void Game::initwindow()
{
	//Creates SFML window using window.ini file

    std::ifstream ifs("Config/window.ini");
    std::string title = "None";
    sf::VideoMode window_bounds(800, 600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();
    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initstates()
{
    this->states.push(new GameState(this->window));
}

//Constructors and destructors
Game::Game()
{
    this->initwindow();
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

