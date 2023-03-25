#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
// ----------------------------------------------------------------------------
#include <SFML\Graphics.hpp>
#include <stack>
// ----------------------------------------------------------------------------
namespace lpa
{
class Screen;
// ----------------------------------------------------------------------------
/**
* Clase cuya responsabilidad es la gestión de todas las clases que representan
* las distintas pantallas en el flow del juego.
*/
class ScreenManager
{
private:
	sf::RenderWindow*		m_window;
	std::stack<Screen*>		m_screens;
	
public:
	ScreenManager(sf::RenderWindow*	m_window);
	~ScreenManager();

	sf::RenderWindow& getRenderWindow() { return *m_window; }

	void addScreen(Screen* screen);
	void removeScreen();
	Screen* getScreen();
	void changeScreen(Screen* screen);
};
// ----------------------------------------------------------------------------
}
#endif // SCREEN_MANAGER_H


