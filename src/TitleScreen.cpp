#include "TitleScreen.h"
// ----------------------------------------------------------------------------
#include "Constants.h"
#include "GameWorld.h"
#include "CreditsScreen.h"
#include "ScreenManager.h"
#include <SFML\Graphics.hpp>
#include <iostream>
// ----------------------------------------------------------------------------
namespace lpa
{
// ----------------------------------------------------------------------------
TitleScreen::TitleScreen(ScreenManager* screenManager)
	: Screen(screenManager)
{
	m_texture.loadFromFile(Constants::pathTitleScreenImage);
	m_sprite.setTexture(m_texture);

	_soundBufferButtonClick.loadFromFile(Constants::clickButtonSound);
	_soundButtonClick.setBuffer(_soundBufferButtonClick);

	_buttons[0]._texture.loadFromFile(Constants::texturePlayButton);
	_buttons[0]._sprite.setTexture(_buttons[0]._texture);
	_buttons[0]._sprite.setPosition(sf::Vector2f(365.f, 443.f));
	_buttons[0]._rect = _buttons[0]._sprite.getGlobalBounds();
	_buttons[0]._visible = false;
	_buttons[1]._texture.loadFromFile(Constants::textureCreditsButton);
	_buttons[1]._sprite.setTexture(_buttons[1]._texture);
	_buttons[1]._sprite.setPosition(sf::Vector2f(364.f, 549.f));
	_buttons[1]._rect = _buttons[1]._sprite.getGlobalBounds();
	_buttons[1]._visible = false;
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			m_screenManager->getRenderWindow().close();
	}

	if (event.type == sf::Event::MouseMoved)
	{
		for (size_t i = 0; i < MAX_BUTTONS; i++)
		{
			if ((event.mouseMove.x >= _buttons[i]._rect.left &&
				event.mouseMove.x <= _buttons[i]._rect.left + _buttons[i]._rect.width) &&
				(event.mouseMove.y >= _buttons[i]._rect.top &&
					event.mouseMove.y <= _buttons[i]._rect.top + _buttons[i]._rect.height))
			{
				_buttons[i]._visible = true;
			}
			else
			{
				_buttons[i]._visible = false;
			}
		}
	}
	
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (_buttons[0]._visible)
		{
			_soundButtonClick.play();
			m_screenManager->changeScreen(new GameWorld(m_screenManager));
		}
		else if (_buttons[1]._visible)
		{
			_soundButtonClick.play();
			m_screenManager->changeScreen(new CreditScreen(m_screenManager));
		}
	}
}

void TitleScreen::update(sf::Time elapsedTime)
{
}

void TitleScreen::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(m_sprite, states);
	for (size_t i = 0; i < MAX_BUTTONS; i++)
	{
		if (_buttons[i]._visible)
			target.draw(_buttons[i]._sprite);
	}
}

// ----------------------------------------------------------------------------
}



