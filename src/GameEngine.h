#pragma once
// -----------------------------------------
#include "pch.h"
#include "screens\ScreenManager.h"
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

		void handleEvents();
		void update(sf::Time elapsedTime);
		void draw();

		static constexpr float k_Fps			{ 60.f };
		static constexpr float k_TimePerFrame	{ 1.f / k_Fps };
	
		sf::RenderWindow	m_window;
		ScreenManager		m_screenManager;
		bool				m_paused;
			
		sf::Texture			m_textureMousePointer;
		sf::Sprite			m_spriteMousePointer;
	};
}
