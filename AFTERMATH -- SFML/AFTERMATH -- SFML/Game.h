#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt; /*dt -- delta time -- keeps track of how long it took
			  for us/our game to do one update calland one render call together.
			  It resets itself after keeping track each time so lasts around some milliseconds.*/ 
	std::stack<State*> states;

	std::map<std::string, int > supportedKeys;

	//Initialization
	void initvariables();
	void initwindow();
	void initkeys();
	void initstates();
	
public:
	//Constructor/Destructors
	Game();
	virtual ~Game();

	//Function

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();
	
	//Render
	void render();
	
	//Core
	void run();
};

#endif