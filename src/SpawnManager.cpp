#include "pch.h"
#include "SpawnManager.h"
// -----------------------------------------
#include "Wave.h"
// -----------------------------------------
namespace lpa
{
	SpawnManager::SpawnManager(Wave& wave)
		: m_spawnPointOne { 0, 768 * 0.75f }
		, m_spawnPointTwo { 1024 - 100, 768 * 0.75f }
		, m_spawnPoints   { m_spawnPointOne, m_spawnPointTwo }
		, m_spawnTime { sf::seconds(10.f) }
		, m_timeSinceLastSpawn { sf::seconds(0.f) }
		, m_wave { wave }
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
		auto& wave { m_wave.get() };
		if (wave.getRemainingEnemies() > 0)
		{
			uint randomPoint { std::rand() % k_MaxSpawnPoints };
			uint indexCurrentEnemy { wave.getIndexCurrentEnemy() };

			Enemy& currentEnemy { wave.getEnemyRefByIndex(indexCurrentEnemy) };
			currentEnemy.setAlive(true);
			currentEnemy.setActive(true);
			currentEnemy.setPosition(m_spawnPoints[randomPoint]);

			wave.increaseIndexCurrentEnemy();
			wave.decreaseRemainingEnemies();

			std::cout << "Spawn Enemy" << std::endl;
		}
	}
}
