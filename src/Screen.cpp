#include "pch.h"
#include "Screen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	Screen::Screen(ScreenManager& screenManager)
		: m_screenManager(screenManager)
	{
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



