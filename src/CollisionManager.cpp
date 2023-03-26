#include "pch.h"
#include "CollisionManager.h"
// -----------------------------------------
#include "AnimatedSprite.h"
// -----------------------------------------
namespace lpa
{
	bool CollisionManager::boundingBoxTest(const AnimatedSprite & Object1, const AnimatedSprite & Object2, float factor)
	{
		sf::FloatRect boundingBoxObj1 = Object1.getGlobalBounds();
		sf::FloatRect boundingBoxObj2 = Object2.getGlobalBounds();

		boundingBoxObj1.left	+= (boundingBoxObj1.width * factor);
		boundingBoxObj1.top		+= (boundingBoxObj1.height * factor);
		boundingBoxObj1.width	*= (1 - factor);
		boundingBoxObj1.height	*= (1 - factor);

		boundingBoxObj2.left	+= (boundingBoxObj2.width * factor);
		boundingBoxObj2.top		+= (boundingBoxObj2.height * factor);
		boundingBoxObj2.width	*= (1 - factor);
		boundingBoxObj2.height	*= (1 - factor);

		if (boundingBoxObj1.intersects(boundingBoxObj2))
			return true;
		else
			return false;
	}
	bool CollisionManager::boundingBoxRangeAttack(const AnimatedSprite & Object1, const AnimatedSprite & Object2, float factor)
	{
		sf::FloatRect boundingBoxObj1 = Object1.getGlobalBounds();
		sf::FloatRect boundingBoxObj2 = Object2.getGlobalBounds();

		boundingBoxObj1.left	+= (boundingBoxObj1.width * factor);
		boundingBoxObj1.top		+= (boundingBoxObj1.height * factor);
		boundingBoxObj1.width	*= (1 - factor);
		boundingBoxObj1.height	*= (1 - factor);

		boundingBoxObj2.left;
		boundingBoxObj2.top;
		boundingBoxObj2.width;
		boundingBoxObj2.height;

		if (boundingBoxObj1.intersects(boundingBoxObj2))
			return true;
		else
			return false;
	}
	bool CollisionManager::pixelTest(const AnimatedSprite& sprite, const sf::Image& mapImage)
	{
		sf::Vector2u spritePosition = static_cast<sf::Vector2u>(sprite.getPosition());
		sf::Color pixelColor = mapImage.getPixel(spritePosition.x, spritePosition.y);

		if (pixelColor == sf::Color::Red)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}