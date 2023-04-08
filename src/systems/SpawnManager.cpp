#include "pch.h"
#include "SpawnManager.h"
// -----------------------------------------
#include "systems\EnemyManager.h"
#include "ecs\MovementCmp.h"
// -----------------------------------------
namespace lpa
{
	SpawnManager::SpawnManager(EnemyManager& EnemyManager)
		: m_spawnPointOne { 0, 768 * 0.75f }
		, m_spawnPointTwo { 1024 - 100, 768 * 0.75f }
		, m_spawnPoints   { m_spawnPointOne, m_spawnPointTwo }
		, m_spawnTime { sf::seconds(5.f) }
		, m_timeSinceLastSpawn { sf::seconds(0.f) }
		, m_EnemyManager { EnemyManager }
	{
	}
	void SpawnManager::update(sf::Time elapsedTime)
	{
		m_timeSinceLastSpawn += elapsedTime;
		if (m_timeSinceLastSpawn >= m_spawnTime)
		{
			spawnEnemies();
			m_timeSinceLastSpawn = sf::seconds(0.f);
		}
	}
	void SpawnManager::spawnEnemies()
	{
		auto& EnemyManager { m_EnemyManager.get() };
		if (EnemyManager.getRemainingEnemies() > 0)
		{
			uint randomPoint { std::rand() % k_MaxSpawnPoints };
			uint indexCurrentEnemy { EnemyManager.getIndexCurrentEnemy() };

			Enemy& currentEnemy { EnemyManager.getEnemyRefByIndex(indexCurrentEnemy) };
			currentEnemy.activate();
			currentEnemy.getComponent<MovementCmp>().position = m_spawnPoints[randomPoint];

			EnemyManager.increaseIndexCurrentEnemy();
			EnemyManager.decreaseRemainingEnemies();

			std::cout << "Spawn Enemy" << std::endl;
		}
	}
}
