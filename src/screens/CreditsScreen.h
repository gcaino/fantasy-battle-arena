#pragma once
// ----------------------------------------------------------------------------
#include "pch.h"
#include "Screen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	class CreditScreen : public Screen
	{
	public:
		CreditScreen(ScreenManager& screenManager);

		void handleEvent(sf::Event event) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite	m_backgroundSprite;
		sf::Font	m_font;
		sf::Text	m_text;
	};
}

