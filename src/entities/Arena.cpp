#include "pch.h"
#include "Arena.h"
// -------------------------------------------------------------------------
#include "AssetManager.h"
// -------------------------------------------------------------------------
namespace lpa
{
	Arena::Arena()
		: m_imageCollision    {}
		, m_spriteCollisionCmp{}
	{
		//m_spriteCmp.getSprite().setTexture(AssetManager<sf::Texture>::GetAssetByKey("arena-01"));
		//
		//auto& sprCollisionCmp = m_spriteCollisionCmp.getSprite();
		//sprCollisionCmp.setTexture(AssetManager<sf::Texture>::GetAssetByKey("collision-arena-01"));
		//m_imageCollision = sprCollisionCmp.getTexture()->copyToImage();

		m_spriteCmp.getSprite().setTexture(AssetManager<sf::Texture>::GetAssetByKey("red-mountain-background"));
	}
}
