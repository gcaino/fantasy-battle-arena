#include "pch.h"
#include "CreditsScreen.h"
// ----------------------------------------------------------------------------
#include "ScreenManager.h"
#include "TextureManager.h"
#include "TitleScreen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	CreditScreen::CreditScreen(ScreenManager& screenManager)
		: Screen(screenManager)
		, m_backgroundSprite {}
	{
		TextureManager::Insert("background-credits", Constants::pathCreditsScreenImage);
		m_backgroundSprite.setTexture(TextureManager::GetTextureByKey("background-credits"));
		
		m_font.loadFromFile(Constants::creditScreenFont);
		m_text.setFont(m_font);
		m_text.setFillColor(sf::Color::Color(9, 18, 51));
		m_text.setStyle(sf::Text::Bold);
		m_text.setCharacterSize(25);

		std::string credits;
		credits = "\t\t\t\tCREDITS\n";
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
			m_screenManager.get().changeScreen(std::make_unique<TitleScreen>(m_screenManager));
	}
	void CreditScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_backgroundSprite, states);
		target.draw(m_text, states);
	}
}



