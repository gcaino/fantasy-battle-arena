#ifndef ARENA_H
#define ARENA_H
// -----------------------------------
#include "GameObject.h"
#include <SFML\Graphics.hpp>
// -----------------------------------
namespace lpa
// -----------------------------------
{
// -----------------------------------
class Arena : public GameObject
{
private:
	sf::Sprite		_spriteCollision;
    sf::Texture     _texture;
	sf::Texture		_textureCollision;
	sf::Image		_imageCollision;

public:
    Arena();
    ~Arena();

	sf::Sprite getSpriteCollision() const	{ return _spriteCollision; }
	sf::Image getImageCollision() const		{ return _imageCollision; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
// -----------------------------------
}
// -----------------------------------
#endif // ARENA_H
