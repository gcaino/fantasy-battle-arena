#include "pch.h"
#include "Arena.h"
// -------------------------------------------------------------------------
#include "AssetManager.h"
// -------------------------------------------------------------------------
namespace lpa
{
	Arena::Arena()
		: m_imageCollision  {}
		, m_spriteCollision {}
	{
		m_sprite.setTexture(AssetManager<sf::Texture>::GetAssetByKey("arena-01"));
		m_spriteCollision.setTexture(AssetManager<sf::Texture>::GetAssetByKey("collision-arena-01"));
		m_imageCollision = m_spriteCollision.getTexture()->copyToImage();
	}
	void Arena::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite);
	}
}
