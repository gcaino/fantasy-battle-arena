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

		virtual void handleEvent(sf::Event event);
		virtual void update(sf::Time elapsedTime);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

	private:
		sf::Font	m_font;
		sf::Text	m_text;
	};
}

