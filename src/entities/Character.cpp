#include "pch.h"
#include "Character.h"
// -----------------------------------------
namespace lpa
{
	Character::Character()
		: m_health(50.f)
		, m_maxHealth(m_health)
		, m_strength(10)
		, m_evasion(0)
		, m_level(1)
		, m_alive(false)
		, m_currentAnimation { std::nullopt }
		, m_animatedSprite(sf::seconds(0.1f), true, false)
		, m_animatedSpriteBlood(sf::seconds(0.1f), true, false)
		, m_active(false)
	{
	}
}
