#include "pch.h"
#include "Character.h"
// -----------------------------------------
namespace lpa
{
	Character::Character()
		: m_position(0.f, 0.f)
		, m_velocity(100.f)
		, m_health(50.f)
		, m_maxHealth(m_health)
		, m_strength(5)
		, m_evasion(0)
		, m_level(1)
		, m_alive(false)
		, m_texture()
		, m_currentAnimation { std::nullopt }
		, m_animatedSprite(sf::seconds(0.1f), true, false)
		, m_animatedSpriteBlood(sf::seconds(0.1f), true, false)
		, m_drawBlood(false)
		, m_active(false)
	{
		m_direction.axisX = DirectionAxis::Right;
		m_prevDirection.axisX = DirectionAxis::Right;
	}
	void Character::calculateDirection()
	{
		m_prevDirection = m_direction;

		if		(m_position.x > m_prevPosition.x)	m_direction.axisX = DirectionAxis::Right;
		else if (m_position.x < m_prevPosition.x)	m_direction.axisX = DirectionAxis::Left;

		if		(m_position.y > m_prevPosition.y)	m_direction.axisY = DirectionAxis::Down;
		else if (m_position.y < m_prevPosition.y)	m_direction.axisY = DirectionAxis::Up;
	}
	void Character::rotateSprite()
	{
		if (m_prevDirection.axisX != m_direction.axisX)
		{
			m_animatedSprite.scale(-1, 1);
		}	
	}
}
