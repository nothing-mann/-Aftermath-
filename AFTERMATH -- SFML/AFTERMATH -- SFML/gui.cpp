#include "stdafx.h"
#include "gui.h"

gui::Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color, short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	//Shape
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	//Text
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x+ (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y+ (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
	//Text color
	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	//Color of button
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

}

gui::Button::~Button()
{

}



//Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const unsigned id)
{
	this->id = id;
}


//Functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	//Update tthe booleans for hover and pressed
	
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		
		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;	
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}




//Dropdown box ============================================================


gui::DropDownBox::DropDownBox(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned noOfElements, unsigned default_index)
	:font(font), showList(false),keytimeMax(1.f), keytime(0.f)
{
	//unsigned noOfElements = sizeof(list) / sizeof(std::string);
	this->activeElement = new gui::Button(
		x, y , width, height, &this->font, list[default_index], 20, sf::Color(255, 255, 255, 150), sf::Color(20, 20, 20, 200), sf::Color(255, 255, 255, 50), sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), sf::Color(255, 255, 255, 200), sf::Color(255,255,255, 255), sf::Color(20, 20, 20, 50)
	);
	for (int i = 0; i < noOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i+1) * height), width, height, &this->font, list[i], 20, sf::Color(255, 255, 255, 150), sf::Color(20,20,20,50), sf::Color(255, 255, 255, 200), sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0), i
			)
		);
	}	
}

gui::DropDownBox::~DropDownBox()
{
	delete this->activeElement;
	for (int i=0; i<this->list.size(); i++)
	{
		delete this->list[i];
	}
}




//Accessors

const unsigned short& gui::DropDownBox::getActiveElementId() const
{
	return this->activeElement->getId();
}

const bool gui::DropDownBox::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}


//functions
void gui::DropDownBox::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}


void gui::DropDownBox::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);
	this->activeElement->update(mousePos);
	

	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);
			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}

}

void gui::DropDownBox::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}



//Texture Selector ============================================================

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text)
{
	this->gridSize = gridSize;

	this->active = false;

	this->hidden = false;

	float offset = 60.f;
	
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50,50,50,100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
	}
	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Green);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->hide_btn = new gui::Button(x, y, 50.f, 50.f, &font, text, 20, sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200), sf::Color(184, 134, 11, 255), sf::Color(218, 165, 32, 255), sf::Color(184, 134, 11, 200));;
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow)
{
	this->hide_btn->update(static_cast<sf::Vector2f>(mousePosWindow));
	
	if (this->hide_btn->isPressed())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}
	
	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->active = true;
		else
			this->active = false;

		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize, this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

			//Update texture rectangle
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
	
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	
	if (!this->hidden)
	{
		target.draw(this->sheet);
		target.draw(this->bounds);


		if (this->active)
			target.draw(this->selector);
	}
	this->hide_btn->render(target);
}
