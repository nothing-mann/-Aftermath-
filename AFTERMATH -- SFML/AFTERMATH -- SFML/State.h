#ifndef STATE_H
#define STATE_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

//Resources are included here like players,
class State
{
private:
	sf::RenderWindow* window;
	std::vector<sf::Texture*> textures;
	bool quit;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;
	virtual void checkForQuit(); // to make sure that basically we can end the state
	virtual void endState() = 0;
	virtual void updateKeybinds(const float& dt) = 0; 
	virtual void update(const float& dt) = 0; // pure virtual function -- we mus include these in our child class and make sure we don't forget these
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif