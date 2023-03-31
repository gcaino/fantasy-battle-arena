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
		, m_drawBlood(false)
		, m_active(false)
	{
	}
}
//#include "pch.h"
//#include "Character.h"
//// -----------------------------------------
//namespace lpa
//{
//	Character::Character()
//		: m_position(0.f, 0.f)
//		, m_velocity(100.f)
//		, m_health(50.f)
//		, m_maxHealth(m_health)
//		, m_strength(10)
//		, m_evasion(0)
//		, m_level(1)
//		, m_alive(false)
//		, m_currentAnimation{ std::nullopt }
//		, m_animatedSprite(sf::seconds(0.1f), true, false)
//		, m_animatedSpriteBlood(sf::seconds(0.1f), true, false)
//		, m_drawBlood(false)
//		, m_active(false)
//	{
//		m_direction.axisX = DirectionAxis::Right;
//		m_prevDirection.axisX = DirectionAxis::Right;
//	}
//
//	void Character::calculateDirection()
//	{
//		if (m_position.x > m_prevPosition.x)	m_direction.axisX = DirectionAxis::Right;
//		else if (m_position.x < m_prevPosition.x)	m_direction.axisX = DirectionAxis::Left;
//
//		if (m_position.y > m_prevPosition.y)	m_direction.axisY = DirectionAxis::Down;
//		else if (m_position.y < m_prevPosition.y)	m_direction.axisY = DirectionAxis::Up;
//	}
//
//	void Character::setPreviousDirection()
//	{
//		if (m_prevDirection.axisX != m_direction.axisX)	m_prevDirection.axisX = m_direction.axisX;
//		else if (m_prevDirection.axisY != m_direction.axisY)	m_prevDirection.axisY = m_direction.axisY;
//	}
//
//	void Character::rotateSprite()
//	{
//		if (m_prevDirection.axisX != m_direction.axisX)
//			m_animatedSprite.scale(-1, 1);
//	}
//}