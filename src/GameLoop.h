#ifndef GAMELOOP_H
#define GAMELOOP_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
class ScreenManager;
// -----------------------------------------
class GameLoop
{
private:
	const unsigned int	FPS;

	sf::RenderWindow	_window;
	sf::Event			_event;
	ScreenManager*		_screenManager;
	bool				_paused;
	sf::Clock			_clock;
	sf::Time			_elapsedTime;
	//GameWorld*			_gameWorld;

	sf::Texture			_textureMousePointer;
	sf::Sprite			_spriteMousePointer;

	void pause();
	void setMousePointer();
	void updateMousePointer();

	void update(sf::Time elapsedTime);
	void draw();

public:
	GameLoop();
	~GameLoop();

	void run();
};
// -----------------------------------------
}
// -----------------------------------------
#endif // GAMELOOP_H