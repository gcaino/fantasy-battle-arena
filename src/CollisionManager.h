#ifndef COLLISION_MANAGER_H
#define	COLLISION_MANAGER_H
// -----------------------------------------
#include "AnimatedSprite.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
class CollisionManager : public sf::Drawable
{
public:
	CollisionManager();
	~CollisionManager();

	//static bool boundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2, float factor = 0.f);
	//static bool CollisionManager::boundingBoxRangeAttack(const sf::Sprite & Object1, const sf::Sprite & Object2, float factor = 0.f);
	//static bool pixelTest(const sf::Sprite& sprite, const sf::Image& mapImage);
	static bool boundingBoxTest(const AnimatedSprite& Object1, const AnimatedSprite& Object2, float factor = 0.f);
	static bool boundingBoxRangeAttack(const AnimatedSprite & Object1, const AnimatedSprite & Object2, float factor = 0.f);
	static bool pixelTest(const AnimatedSprite& sprite, const sf::Image& mapImage);
};
// -----------------------------------------
}
// -----------------------------------------
#endif // !COLLISION_MANAGER_H
