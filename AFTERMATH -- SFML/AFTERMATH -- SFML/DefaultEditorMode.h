#pragma once
#include "EditorMode.h"
class DefaultEditorMode :
    public EditorMode
{
private:
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    gui::TextureSelector* textureSelector;

    sf::IntRect textureRect;
    bool collision;
    short type;

    int layer;
    bool tileAddLock;


    void initVariables();
    void initGui();

public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~DefaultEditorMode();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

