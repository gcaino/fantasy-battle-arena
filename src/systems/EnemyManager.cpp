#include "pch.h"
#include "EnemyManager.h"
// -----------------------------------------
#include "entities\Player.h"
// -----------------------------------------
namespace lpa
{
	EnemyManager::EnemyManager()
		: m_enemies {}
		, m_remainingEnemies { k_MaxEnemies }
		, m_indexCurrentEnemy { 0 }
	{
	}
	void EnemyManager::update(sf::Time elapsedTime, Player& player)
	{
		for (auto& enemy : m_enemies)
		{
			if (enemy.isAlive())
				enemy.update(elapsedTime, player);
		}
	}
	void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& enemy : m_enemies)
		{
			if (enemy.isAlive())
				enemy.draw(target, states);
		}
	}
}
