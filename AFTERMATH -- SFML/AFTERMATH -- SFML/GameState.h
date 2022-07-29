#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
class GameState :
    public State
{
private:
     
public:

    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    //Functions

    void endState();
    void updateKeybinds(const float& dt);
    void update(const float& dt); // was a pure virtual function of State
    void render(sf::RenderTarget* target = nullptr); // was a pure virtual function of State
};

#endif