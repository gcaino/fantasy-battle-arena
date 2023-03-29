#include "pch.h"
#include "Arena.h"
// -------------------------------------------------------------------------
#include "TextureManager.h"
// -------------------------------------------------------------------------
namespace lpa
{
	Arena::Arena()
		: m_imageCollision  {}
		, m_spriteCollision {}
	{
		m_sprite.setTexture(TextureManager::GetTextureByKey("arena-01"));
		m_spriteCollision.setTexture(TextureManager::GetTextureByKey("collision-arena-01"));
		m_imageCollision = m_spriteCollision.getTexture()->copyToImage();
	}
	void Arena::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite);
	}
}
