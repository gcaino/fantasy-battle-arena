#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H
// ----------------------------------------------------------------------------
#include "Screen.h"
#include <SFML\Audio.hpp>
// ----------------------------------------------------------------------------
namespace lpa
{
// ----------------------------------------------------------------------------
struct Button
{
	bool			_visible;
	sf::FloatRect	_rect;
	sf::Texture		_texture;
	sf::Sprite		_sprite;
};
const int MAX_BUTTONS = 2;
// ----------------------------------------------------------------------------
class TitleScreen : public Screen
{
private:
	Button				_buttons[2];
	sf::SoundBuffer		_soundBufferButtonClick;
	sf::Sound			_soundButtonClick;

public:
	TitleScreen(ScreenManager* screenManager);
	~TitleScreen();

	virtual void handleEvent(sf::Event event);
	virtual void update(sf::Time elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
};
// ----------------------------------------------------------------------------
}
#endif // TITLE_SCREEN_H


