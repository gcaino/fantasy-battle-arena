#include "pch.h"
#include "GameLoop.h"
// -----------------------------------------
#include "GameWorld.h"
#include "ScreenManager.h"
#include "TitleScreen.h"
// -----------------------------------------
namespace lpa
{
	GameLoop::GameLoop()
		: m_paused(false)
	{
		m_window.create(sf::VideoMode(Constants::k_WindowWidth,
									  Constants::k_WindowHeight), Constants::k_WindowTitle.data());
		m_window.setFramerateLimit(k_Fps);
		setMousePointer();
	
		m_screenManager = new ScreenManager(&m_window);
		m_screenManager->addScreen(new TitleScreen(m_screenManager));
	}	
	GameLoop::~GameLoop()
	{	
		m_screenManager->removeScreen();
		delete m_screenManager;
	}	
	void GameLoop::run()
	{	
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
	
				m_screenManager->getScreen()->handleEvent(event);
			}
			m_screenManager->getScreen()->handleInput();
	
			m_elapsedTime = m_clock.restart();
			update(m_elapsedTime);
	
			draw();
		}
	}	
	void GameLoop::update(sf::Time elapsedTime)
	{	
		updateMousePointer();
	
		if (!m_paused)
			m_screenManager->getScreen()->update(m_elapsedTime);
	}	
	void GameLoop::draw()
	{	
		m_window.clear();
		m_screenManager->getScreen()->draw(m_window, sf::RenderStates::Default);
		m_window.draw(m_spriteMousePointer, sf::RenderStates::Default);
		m_window.display();
	}	
	void GameLoop::pause()
	{	
		(m_paused) ? m_paused = false : m_paused = true;
	}	
	void GameLoop::setMousePointer()
	{	
		m_window.setMouseCursorVisible(false);
		m_textureMousePointer.loadFromFile(Constants::texturesPathMousePointerAxe);
		m_spriteMousePointer.setTexture(m_textureMousePointer);
	
		sf::Vector2f mousePointerOrigin;
		mousePointerOrigin.x = m_spriteMousePointer.getGlobalBounds().width / 2;
		mousePointerOrigin.y = m_spriteMousePointer.getLocalBounds().height / 2;
		m_spriteMousePointer.setOrigin(mousePointerOrigin);
	}	
	void GameLoop::updateMousePointer()
	{	
		sf::Vector2i mousePosition = static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window));
		m_spriteMousePointer.setPosition(static_cast<sf::Vector2f>(mousePosition));
	}
}
