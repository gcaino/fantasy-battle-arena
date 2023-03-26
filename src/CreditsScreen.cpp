#include "pch.h"
#include "CreditsScreen.h"
// ----------------------------------------------------------------------------
#include "Constants.h"
#include "TitleScreen.h"
#include "ScreenManager.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	CreditScreen::CreditScreen(ScreenManager* screenManager)
		: Screen(screenManager)
	{
		m_texture.loadFromFile(Constants::pathCreditsScreenImage);
		m_sprite.setTexture(m_texture);
		m_font.loadFromFile(Constants::creditScreenFont);
		m_text.setFont(m_font);
		m_text.setFillColor(sf::Color::Color(9, 18, 51));
		m_text.setStyle(sf::Text::Bold);
		m_text.setCharacterSize(25);

		std::string credits;
		credits = "\t\t\t\tCREDITS\n";
		credits.append("Profesor: Sergio Baretto\n\n");
		credits.append("Diseño: Germán Caíno\n");
		credits.append("Programación: Germán Caíno\n");
		credits.append("Arte: https://craftpix.net/ \n");
		credits.append("Sonido: n Beats \n");
		m_text.setString(credits);
		m_text.setPosition(350.f, 180.f);
	}
	void CreditScreen::handleEvent(sf::Event event)
	{
		if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
			m_screenManager->changeScreen(new TitleScreen(m_screenManager));
	}

	void CreditScreen::update(sf::Time elapsedTime)
	{
	}

	void CreditScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}

	void CreditScreen::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		target.draw(m_sprite, states);
		target.draw(m_text, states);
	}
}



