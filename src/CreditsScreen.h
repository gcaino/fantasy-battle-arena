#ifndef CREDIT_SCREEN_H
#define CREDIT_SCREEN_H
// ----------------------------------------------------------------------------
#include "Screen.h"
#include <SFML\Graphics.hpp>
// ----------------------------------------------------------------------------
namespace lpa
{
// ----------------------------------------------------------------------------
class CreditScreen : public Screen
{
private:
	sf::Font	m_font;
	sf::Text	m_text;

public:
	CreditScreen(ScreenManager* screenManager);
	~CreditScreen();

	virtual void handleEvent(sf::Event event);
	virtual void update(sf::Time elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
};
// ----------------------------------------------------------------------------
}
#endif // GAMEOVER_SCREEN_H
