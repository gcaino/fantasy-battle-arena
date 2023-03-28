#pragma once
// ----------------------------------------------------------------------------
#include "pch.h"
#include "Screen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	class ScreenManager
	{
	public:
		ScreenManager(sf::RenderWindow& m_window);

		constexpr sf::RenderWindow& getRenderWindow()		noexcept  { return m_window; }
		constexpr sf::RenderWindow& getRenderWindow() const noexcept  { return m_window; }

		void addScreen(UPtr<Screen> screen);
		void changeScreen(UPtr<Screen> screen);
		void removeScreen();

		const Screen& getScreen() const;
		Screen& getScreen();
		
	private:
		using Screens = std::stack<UPtr<Screen>>;

		Screens					m_screens;
		Ref<sf::RenderWindow>	m_window;
	};
}


