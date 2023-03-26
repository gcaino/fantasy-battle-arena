#pragma once
// -----------------------------------------
#include "pch.h"
// -----------------------------------------
namespace lpa
{
	class ScreenManager;
	// -----------------------------------------
	class GameLoop
	{
	public:
		GameLoop();
		~GameLoop();

		void run();

	private:
		void pause();
		void setMousePointer();
		void updateMousePointer();

		void update(sf::Time elapsedTime);
		void draw();

		static constexpr unsigned int k_Fps { 60 };
	
		sf::RenderWindow	m_window;
		ScreenManager*		m_screenManager;
		bool				m_paused;
		sf::Clock			m_clock;
		sf::Time			m_elapsedTime;
						
		sf::Texture			m_textureMousePointer;
		sf::Sprite			m_spriteMousePointer;
	};
}
