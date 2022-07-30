#ifndef STATE_H
#define STATE_H

#include "Player.h"

//Resources are included here like players,
class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	
	//For mouse positions in our game
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;
public:
	
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
 // to make sure that basically we can end the state
	virtual void endState();

	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0; 
	virtual void update(const float& dt) = 0; // pure virtual function -- we mus include these in our child class and make sure we don't forget these
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif