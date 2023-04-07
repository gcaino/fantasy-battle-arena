#pragma once
// --------------------------------------------------------------------------------
#include "pch.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	class SpriteCmp : public sf::Drawable
	{
	public:
		SpriteCmp() = default;

		const sf::Sprite& getSprite() const noexcept { return m_sprite; }
			  sf::Sprite& getSprite()		noexcept { return m_sprite; }

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite m_sprite    {};
	};
}
