#ifndef STATE_H
#define STATE_H

class State;

#include "Player.h"
#include "GraphicsSettings.h"

class StateData
{
public:
	StateData() {};
	//Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map < std::string, int >* supportedKeys; 
	std::stack<State*>* states;
	

};
//Resources are included here like players,
class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;
	
	//For mouse positions in our game
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;
public:
	
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	
	//Functions


 // to make sure that basically we can end the state
	virtual void endState();
	void pauseState();
	void unpausedState();

	
	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0; 
	virtual void update(const float& dt) = 0; // pure virtual function -- we mus include these in our child class and make sure we don't forget these
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif