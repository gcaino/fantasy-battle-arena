#include "Arena.h"
// ---------------------------
#include "Constants.h"
#include <SFML\Graphics.hpp>
// ---------------------------
namespace lpa
// ---------------------------
{
// ---------------------------
Arena::Arena()
{
	_texture.loadFromFile(Constants::texturePathArena);
	_textureCollision.loadFromFile(Constants::texturePathArenaCollision);
    _sprite.setTexture(_texture);
	_spriteCollision.setTexture(_textureCollision);
	_imageCollision = _textureCollision.copyToImage();
}
Arena::~Arena()
{
}
void Arena::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}
// ---------------------------
}
