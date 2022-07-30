#ifndef STATE_H
#define STATE_H

#include "Entity.h"

//Resources are included here like players,
class State
{
private:
protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	
	//Resources
	std::vector<sf::Texture*> textures;

	//Functions
	virtual void initKeybinds() = 0;
public:
	
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	const bool& getQuit() const;
	virtual void checkForQuit(); // to make sure that basically we can end the state
	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0; 
	virtual void update(const float& dt) = 0; // pure virtual function -- we mus include these in our child class and make sure we don't forget these
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif