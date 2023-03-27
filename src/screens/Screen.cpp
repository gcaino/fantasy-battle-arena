#include "pch.h"
#include "Screen.h"
// ----------------------------------------------------------------------------
#include "ScreenManager.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	Screen::Screen(ScreenManager& screenManager)
		: m_screenManager(screenManager)
	{
		auto& window { m_screenManager.get().getRenderWindow() };
		window.setMouseCursorVisible(true);
	}
	void Screen::handleInput()
	{
	}
	void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite, states);
	}
	void Screen::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		target.draw(m_sprite, states);
	}
}



