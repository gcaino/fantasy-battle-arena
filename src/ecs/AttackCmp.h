#pragma once
// --------------------------------------------------------------------------------
#include "pch.h"
#include "ecs\Component.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	class Enemy;
	class EnemyManager;

	class AttackCmp : public Component
	{
	public:
		AttackCmp();

		bool isAttacking() const { return m_attacking; }
		void setAttacking(bool attacking) { m_attacking = attacking; }
		uint getEnemiesKilled() const { return m_enemiesKilled; }
		void addEnemyKilled() { ++m_enemiesKilled; }

	private:
		std::list<Ref<Enemy>>	m_attackablesEnemies;

		sf::Time			m_speedAttack;
		sf::Time			m_timeSinceLastAttack;
		sf::Clock			m_clockAttack;
		bool				m_attacking;

		float				m_rangeAttack;
		uint				m_enemiesKilled;
	};
}
