#pragma once
// -----------------------------------------
#include "pch.h"
#include "ScreenManager.h"
// -----------------------------------------
namespace lpa
{
	class GameEngine
	{
	public:
		GameEngine();

		void run();

	private:
		void pause();
		void setMousePointer();
		void updateMousePointer();

		void update(sf::Time elapsedTime);
		void draw();

		static constexpr unsigned int k_Fps { 60 };
	
		sf::RenderWindow	m_window;
		ScreenManager		m_screenManager;
		sf::Clock			m_clock;
		sf::Time			m_elapsedTime;
		bool				m_paused;
			
		sf::Texture			m_textureMousePointer;
		sf::Sprite			m_spriteMousePointer;
	};
}
