#include "pch.h"
#include "GameEngine.h"
// -----------------------------------------
#include "TitleScreen.h"
// -----------------------------------------
namespace lpa
{
	GameEngine::GameEngine()
		: m_window{}
		, m_screenManager{ m_window }
		, m_clock{}
		, m_elapsedTime{}
		, m_paused{ false }
		, m_textureMousePointer{}
		, m_spriteMousePointer{}
	{
		m_window.create(sf::VideoMode(Constants::k_WindowWidth,
									  Constants::k_WindowHeight), Constants::k_WindowTitle.data());
		m_window.setFramerateLimit(k_Fps);
		setMousePointer();
	
		m_screenManager.addScreen(std::make_unique<TitleScreen>(m_screenManager));
	}	
	void GameEngine::run()
	{	
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
	
				m_screenManager.getScreen().handleEvent(event);
			}
			m_screenManager.getScreen().handleInput();
	
			m_elapsedTime = m_clock.restart();
			update(m_elapsedTime);
	
			draw();
		}
	}	
	void GameEngine::update(sf::Time elapsedTime)
	{	
		updateMousePointer();
	
		if (!m_paused)
			m_screenManager.getScreen().update(m_elapsedTime);
	}	
	void GameEngine::draw()
	{	
		m_window.clear();
		m_screenManager.getScreen().draw(m_window, sf::RenderStates::Default);
		m_window.draw(m_spriteMousePointer, sf::RenderStates::Default);
		m_window.display();
	}	
	void GameEngine::pause()
	{	
		(m_paused) ? m_paused = false : m_paused = true;
	}	
	void GameEngine::setMousePointer()
	{	
		m_window.setMouseCursorVisible(false);
		m_textureMousePointer.loadFromFile(Constants::texturesPathMousePointerAxe);
		m_spriteMousePointer.setTexture(m_textureMousePointer);
	
		sf::Vector2f mousePointerOrigin;
		mousePointerOrigin.x = m_spriteMousePointer.getGlobalBounds().width / 2;
		mousePointerOrigin.y = m_spriteMousePointer.getLocalBounds().height / 2;
		m_spriteMousePointer.setOrigin(mousePointerOrigin);
	}	
	void GameEngine::updateMousePointer()
	{	
		sf::Vector2i mousePosition = static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window));
		m_spriteMousePointer.setPosition(static_cast<sf::Vector2f>(mousePosition));
	}
}
