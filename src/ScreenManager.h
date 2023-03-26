#pragma once
// ----------------------------------------------------------------------------
#include "pch.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	class Screen;
	// ------------------------------------------------------------------------
	class ScreenManager
	{
	public:
		ScreenManager(sf::RenderWindow* m_window);

		sf::RenderWindow& getRenderWindow() { return *m_window; }

		void addScreen(Screen* screen);
		void removeScreen();
		Screen* getScreen();
		void changeScreen(Screen* screen);

	private:
		sf::RenderWindow*		m_window;
		std::stack<Screen*>		m_screens;
	
	};
}


