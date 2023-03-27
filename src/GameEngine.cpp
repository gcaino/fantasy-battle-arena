#include "pch.h"
#include "GameEngine.h"
// -----------------------------------------
#include "screens\TitleScreen.h"
// -----------------------------------------
namespace lpa
{
	GameEngine::GameEngine()
		: m_window{}
		, m_screenManager{ m_window }

	{
		m_window.create(sf::VideoMode(Constants::k_WindowWidth,
									  Constants::k_WindowHeight), Constants::k_WindowTitle.data());
		m_screenManager.addScreen(std::make_unique<TitleScreen>(m_screenManager));
	}	
	void GameEngine::run()
	{	
		sf::Clock clock {};
		sf::Time  elapsedTime{ sf::Time::Zero };
		sf::Time  timePerFrame{ sf::seconds(k_TimePerFrame) };
		while (m_window.isOpen())
		{
			handleEvents();

			elapsedTime += clock.restart();
			while (elapsedTime > timePerFrame)
			{
				elapsedTime -= timePerFrame;
				update(timePerFrame);
			}

			draw();
		}
	}	
	void GameEngine::handleEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();

			m_screenManager.getScreen().handleEvent(event);
		}
	}
	void GameEngine::update(sf::Time elapsedTime)
	{	
		m_screenManager.getScreen().handleInput();
		m_screenManager.getScreen().update(elapsedTime);
	}	
	void GameEngine::draw()
	{	
		m_window.clear();
		m_screenManager.getScreen().draw(m_window, sf::RenderStates::Default);
		m_window.display();
	}		
}
