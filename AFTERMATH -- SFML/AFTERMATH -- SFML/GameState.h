#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
class GameState :
    public State
{
private:
    Entity player;

    //Functions
    void initKeybinds();
public:

    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~GameState();

    //Functions

    void endState();
    void updateInput(const float& dt);
    void update(const float& dt); // was a pure virtual function of State
    void render(sf::RenderTarget* target = nullptr); // was a pure virtual function of State
};

#endif