#pragma once
// -----------------------------------
#include "pch.h"
#include "ecs\SpriteCmp.h"
// -----------------------------------
namespace lpa
{
	class Arena
	{
	public:
		Arena();

		const sf::Sprite& getSpriteCollision() const { return m_spriteCollisionCmp.getSprite(); }
		const sf::Image& getImageCollision() const   { return m_imageCollision; }
		
		const SpriteCmp& getSprCmp() const { return m_spriteCmp; }
		const SpriteCmp& getSprCollisionCmp() const { return m_spriteCollisionCmp; }

	private:		
		SpriteCmp	m_spriteCmp;
		SpriteCmp	m_spriteCollisionCmp;
		sf::Image	m_imageCollision;
	};
}
