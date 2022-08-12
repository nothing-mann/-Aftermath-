#include "stdafx.h"
#include "EditorState.h"

//Initializer functions
void EditorState::initVariables()
{
	this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;

	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;

}

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->view.setCenter(
		this->stateData->gfxSettings->resolution.width / 2.f,
		this->stateData->gfxSettings->resolution.height / 2.f
	);
}


void EditorState::initFonts()
{
	this->font.loadFromFile("Fonts/Pixellettersfull.ttf");
	//{
	//	throw("ERROR::EditorSTATE::COULD NOT LOAD FONT");//throw() -- Exits a program and tells us what happened (Error message is displayed)
	//}
}



void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void EditorState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), gui::calcCharSize(vm), "Quit");
	this->pmenu->addButton("SAVE", gui::p2pY(46.3f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), gui::calcCharSize(vm), "Save");
	this->pmenu->addButton("LOAD", gui::p2pY(37.f, vm), gui::p2pX(26.04f, vm), gui::p2pY(9.25f, vm), gui::calcCharSize(vm), "Load");
}


void EditorState::initButtons()
{
	//sf::Keyboard::Key
}

void EditorState::initGui()
{
	


}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
}

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

	this->initModes();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pmenu;
	delete this->tileMap;


	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}




void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpausedState();
	}

}

void EditorState::updateEditorInput(const float& dt)
{
	//Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -/*std::floor(*/this->cameraSpeed * dt);  //std::floor limits the value to one decimal 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, /*std::floor(*/ this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move( -/*std::floor(*/this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(/*std::floor(*/this->cameraSpeed * dt, 0.f);
	}
}

void EditorState::updateButtons()
{
	//Updates all the buttons in the statte and handles thei functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	
}

void EditorState::updateGui(const float& dt)
{
	
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		this->endState();
	if (this->pmenu->isButtonPressed("SAVE"))
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		this->tileMap->saveToFile("text.ammp");
	if (this->pmenu->isButtonPressed("LOAD"))
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		this->tileMap->loadFromFile("text.ammp");
}

void EditorState::updateModes(const float& dt)
{
	this->modes[EditorModes::DEFAULT_MODE]->update(dt);
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

	system("cls");
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";

	

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
}

void EditorState::renderModes(sf::RenderTarget& target)
{
	this->modes[EditorModes::DEFAULT_MODE]->render(target);
}


void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid, NULL, sf::Vector2f(), true);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	this->renderGui(*target);

	this->renderModes(*target);

	if (this->paused) //Paused menu render
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}


}