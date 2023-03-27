#pragma once
// -----------------------------------
#include "pch.h"
// -----------------------------------
namespace lpa
{
	class GameObject : public sf::Drawable
	{
	public:
		GameObject() = default;

		sf::Sprite	getSprite() const { return m_sprite; }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::Sprite m_sprite;
	};
}