#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"

class GameState :
    public State
{
private:
    Player* player;

    //Functions
    void initKeybinds();
    void initTextures();
    void initPlayers();
public:

    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions


    void updateInput(const float& dt);
    void update(const float& dt); // was a pure virtual function of State
    void render(sf::RenderTarget* target = nullptr); // was a pure virtual function of State
};

#endif