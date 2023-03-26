#include "pch.h"
#include "Arena.h"
// ---------------------------
namespace lpa
{
	Arena::Arena()
	{
		m_texture.loadFromFile(Constants::texturePathArena);
		m_textureCollision.loadFromFile(Constants::texturePathArenaCollision);
		m_sprite.setTexture(m_texture);
		m_spriteCollision.setTexture(m_textureCollision);
		m_imageCollision = m_textureCollision.copyToImage();
	}
	void Arena::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite);
	}
}
