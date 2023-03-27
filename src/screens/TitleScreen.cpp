#include "pch.h"
#include "TitleScreen.h"
// ----------------------------------------------------------------------------
#include "ScreenManager.h"
#include "GameplayScreen.h"
#include "CreditsScreen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	TitleScreen::TitleScreen(ScreenManager& screenManager)
		: Screen(screenManager)
		, m_backgroundTexture{}
		, m_backgroundSprite {}
	{
		m_backgroundTexture.loadFromFile(Constants::pathTitleScreenImage);
		m_backgroundSprite.setTexture(m_backgroundTexture);

		m_soundBufferButtonClick.loadFromFile(Constants::clickButtonSound);
		m_soundButtonClick.setBuffer(m_soundBufferButtonClick);
		
		// Button: "Play Now"
		m_buttons[0].texture.loadFromFile(Constants::texturePlayButton);
		m_buttons[0].sprite.setTexture(m_buttons[0].texture);
		m_buttons[0].sprite.setPosition(sf::Vector2f(365.f, 443.f));
		m_buttons[0].rect = m_buttons[0].sprite.getGlobalBounds();
		m_buttons[0].visible = false;
		// Button: "Credits"
		m_buttons[1].texture.loadFromFile(Constants::textureCreditsButton);
		m_buttons[1].sprite.setTexture(m_buttons[1].texture);
		m_buttons[1].sprite.setPosition(sf::Vector2f(364.f, 549.f));
		m_buttons[1].rect = m_buttons[1].sprite.getGlobalBounds();
		m_buttons[1].visible = false;
	}
	void TitleScreen::handleEvent(sf::Event event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				m_screenManager.get().getRenderWindow().close();
		}

		if (event.type == sf::Event::MouseMoved)
		{
			for (size_t i = 0; i < k_MaxButtons; i++)
			{
				if ((event.mouseMove.x >= m_buttons[i].rect.left &&
					 event.mouseMove.x <= m_buttons[i].rect.left + m_buttons[i].rect.width) &&
					(event.mouseMove.y >= m_buttons[i].rect.top &&
					 event.mouseMove.y <= m_buttons[i].rect.top + m_buttons[i].rect.height))
				{
					m_buttons[i].visible = true;
				}
				else
				{
					m_buttons[i].visible = false;
				}
			}
		}
	
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (m_buttons[0].visible)
			{
				m_soundButtonClick.play();
				m_screenManager.get().changeScreen(std::make_unique<GameplayScreen>(m_screenManager));
			}
			else if (m_buttons[1].visible)
			{
				m_soundButtonClick.play();
				m_screenManager.get().changeScreen(std::make_unique<CreditScreen>(m_screenManager));
			}
		}
	}
	void TitleScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_backgroundSprite, states);
		for (const auto& button : m_buttons)
		{
			if (button.visible)
				target.draw(button.sprite);
		}
	}
}



