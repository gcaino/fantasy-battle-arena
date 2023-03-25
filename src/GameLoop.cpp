#include "GameLoop.h"
// -----------------------------------------
#include "Constants.h"
#include "GameWorld.h"
#include "ScreenManager.h"
#include "TitleScreen.h"
#include <SFML\Graphics.hpp>
#include <iostream>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
GameLoop::GameLoop()
	: _paused(false)
	, FPS(60)
{
	_window.create(sf::VideoMode(Constants::WINDOW_WIDTH_MAX,
								 Constants::WINDOW_HEIGHT_MAX), "Final Project LPA");
	_window.setFramerateLimit(FPS);
	setMousePointer();

	_screenManager = new ScreenManager(&_window);
	_screenManager->addScreen(new TitleScreen(_screenManager));
}
GameLoop::~GameLoop()
{
	_screenManager->removeScreen();
	delete _screenManager;
}
void GameLoop::run()
{
	while (_window.isOpen())
	{
		while (_window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				_window.close();

			_screenManager->getScreen()->handleEvent(_event);
		}
		_screenManager->getScreen()->handleInput();

		_elapsedTime = _clock.restart();
		update(_elapsedTime);

		draw();
	}
}
void GameLoop::update(sf::Time elapsedTime)
{
	updateMousePointer();

	if (!_paused)
		_screenManager->getScreen()->update(_elapsedTime);
}
void GameLoop::draw()
{
	_window.clear();
	_screenManager->getScreen()->draw(_window, sf::RenderStates::Default);
	_window.draw(_spriteMousePointer, sf::RenderStates::Default);
	_window.display();
}
void GameLoop::pause()
{
	(_paused) ? _paused = false : _paused = true;
}
void GameLoop::setMousePointer()
{
	_window.setMouseCursorVisible(false);
	_textureMousePointer.loadFromFile(Constants::texturesPathMousePointerAxe);
	_spriteMousePointer.setTexture(_textureMousePointer);

	sf::Vector2f mousePointerOrigin;
	mousePointerOrigin.x = _spriteMousePointer.getGlobalBounds().width / 2;
	mousePointerOrigin.y = _spriteMousePointer.getLocalBounds().height / 2;
	_spriteMousePointer.setOrigin(mousePointerOrigin);
}
void GameLoop::updateMousePointer()
{
	sf::Vector2i mousePosition = static_cast<sf::Vector2i>(sf::Mouse::getPosition(_window));
	_spriteMousePointer.setPosition(static_cast<sf::Vector2f>(mousePosition));
}
// -----------------------------------------
}
