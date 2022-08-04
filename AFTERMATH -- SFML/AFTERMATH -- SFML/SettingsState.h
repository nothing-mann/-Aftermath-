#pragma once
#include "State.h"
#include "gui.h"
#include "GraphicsSettings.h"


class SettingsState :
    public State
{
private:
    //Variables
    GraphicsSettings& gfxSettings;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*>buttons;
    std::map<std::string, gui::DropDownBox*> dropDownLists;

    sf::Text optionsText;
    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();
public:
    SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();


    //Accessors

    //Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

