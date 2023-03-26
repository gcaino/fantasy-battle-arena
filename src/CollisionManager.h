#pragma once
// -----------------------------------------
#include "pch.h"
#include "AnimatedSprite.h"
// -----------------------------------------
namespace lpa
{
	class CollisionManager : public sf::Drawable
	{
	public:
		CollisionManager() = default;

		static bool boundingBoxTest(const AnimatedSprite& Object1, const AnimatedSprite& Object2, float factor = 0.f);
		static bool boundingBoxRangeAttack(const AnimatedSprite & Object1, const AnimatedSprite & Object2, float factor = 0.f);
		static bool pixelTest(const AnimatedSprite& sprite, const sf::Image& mapImage);
	};
}
