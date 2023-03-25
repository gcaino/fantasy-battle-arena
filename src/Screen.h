#ifndef SCREEN_H
#define SCREEN_H
// ----------------------------------------------------------------------------
#include <SFML\Graphics.hpp>
// ----------------------------------------------------------------------------
namespace lpa
{
// ----------------------------------------------------------------------------
class ScreenManager;
// ----------------------------------------------------------------------------
/**
* Clase Abstracta de la cual heredan todas las clases que representan pantallas
* en el flow del juego.
*/
class Screen : public sf::Drawable
{
protected:
	sf::Texture		m_texture;
	sf::Sprite		m_sprite;
	ScreenManager*	m_screenManager;

public:
	Screen(ScreenManager* screenManager);
	virtual ~Screen();

	virtual void handleInput();
	virtual void handleEvent(sf::Event event) = 0;
	virtual void update(sf::Time elapsedTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
};
// ----------------------------------------------------------------------------
}
#endif // SCREEN_H
