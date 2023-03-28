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
		, m_buttons{{ui::Button{m_screenManager.get().getRenderWindow()}, ui::Button{m_screenManager.get().getRenderWindow()}}}
	{
		m_backgroundTexture.loadFromFile(Constants::pathTitleScreenImage);
		m_backgroundSprite.setTexture(m_backgroundTexture);

		m_soundBufferButtonClick.loadFromFile(Constants::clickButtonSound);
		m_soundButtonClick.setBuffer(m_soundBufferButtonClick);
		
		// Button: "Play Now"
		m_buttons[0].setTexture(Constants::texturePlayButton);
		m_buttons[0].setPosition(sf::Vector2f(365.f, 443.f));

		auto playBtnCallback = [&sndBtnClick = m_soundButtonClick, &screenManager = m_screenManager]() {
			sndBtnClick.play();
			screenManager.get().changeScreen(std::make_unique<GameplayScreen>(screenManager));
		};
		m_buttons[0].setCallback(playBtnCallback);

		// Button: "Credits"
		m_buttons[1].setTexture(Constants::textureCreditsButton);
		m_buttons[1].setPosition(sf::Vector2f(364.f, 549.f));

		auto creditsBtnCallback = [&sndBtnClick = m_soundButtonClick, &screenManager = m_screenManager]() {
			sndBtnClick.play();
			sf::sleep(sf::seconds(0.25f));
			screenManager.get().changeScreen(std::make_unique<CreditScreen>(screenManager));
		};
		m_buttons[1].setCallback(creditsBtnCallback);
	}
	void TitleScreen::handleEvent(sf::Event event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				m_screenManager.get().getRenderWindow().close();
		}

		for (auto& button : m_buttons)
		{
			if (button.isMouseOver())
			{
				if (!button.isActive())
					button.activate();
			}
			else
			{
				if (button.isActive())
					button.deactivate();
			}

			if (button.isActive() && 
				event.type == sf::Event::MouseButtonPressed)
			{
				button.click();
				break;
			}
		}
	}
	void TitleScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_backgroundSprite, states);
		for (const auto& button : m_buttons)
			button.draw();
	}
}



