#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
// -----------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------
namespace lpa
// -----------------------------------
{
// -----------------------------------
class GameObject : public sf::Drawable
{
protected:
	sf::Sprite      _sprite;

public:
	GameObject();
	~GameObject();

	sf::Sprite		getSprite() const { return _sprite; }
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
// -----------------------------------
}
#endif GAME_OBJECT_H