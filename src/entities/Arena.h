#pragma once
// -----------------------------------
#include "pch.h"
#include "entities\GameObject.h"
// -----------------------------------
namespace lpa
{
	class Arena : public GameObject
	{
	public:
		Arena();

		const sf::Sprite& getSpriteCollision() const { return m_spriteCollision; }
		const sf::Image& getImageCollision() const   { return m_imageCollision; }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:			
		sf::Image	m_imageCollision;
		sf::Sprite	m_spriteCollision;
	};
}
