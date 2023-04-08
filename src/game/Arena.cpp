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
		auto& sprCollisionCmp = m_spriteCollisionCmp.getSprite();
		sprCollisionCmp.setTexture(AssetManager<sf::Texture>::GetAssetByKey("collision-palace-battleground"));
		m_imageCollision = sprCollisionCmp.getTexture()->copyToImage();

		m_spriteCmp.getSprite().setTexture(AssetManager<sf::Texture>::GetAssetByKey("palace-battleground"));
	}
}
