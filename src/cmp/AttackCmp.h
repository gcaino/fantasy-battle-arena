#pragma once
// --------------------------------------------------------------------------------
#include "pch.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	class Enemy;
	class EnemyManager;

	class AttackCmp
	{
	public:
		AttackCmp();

		bool isAttacking() const { return m_attacking; }
		void setAttacking(bool attacking) { m_attacking = attacking; }
		uint getEnemiesKilled() const { return m_enemiesKilled; }
		void addEnemyKilled() { ++m_enemiesKilled; }

		//void attack(Enemy& enemy);
		//void takeDamage(uint damage);
		//void addAttackableEnemy(Enemy& enemy);
		//void removeAttackableEnemy(Enemy& enemy);
		//bool isItemAttackablesEnemiesList(const Enemy& enemy);
		//void handlerInputsAttack(EnemyManager& EnemyManager, const sf::RenderWindow& window);
		//uint calculateDamage();
		//void verifyDeath(sf::Time elapsedTime);

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
