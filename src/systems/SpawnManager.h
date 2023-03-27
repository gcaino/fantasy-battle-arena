#pragma once
// -----------------------------------------
#include "pch.h"
// -----------------------------------------
namespace lpa
{
	class EnemyManager;
	// -----------------------------------------
	class SpawnManager
	{
	public:
		SpawnManager(EnemyManager& EnemyManager);

		void update(sf::Time elapsedTime);

	private:
		static constexpr uint k_MaxSpawnPoints { 2 };
		
		sf::Vector2f  m_spawnPointOne;
		sf::Vector2f  m_spawnPointTwo;
		sf::Vector2f  m_spawnPoints[k_MaxSpawnPoints];
		
		sf::Time	  m_spawnTime;
		sf::Time	  m_timeSinceLastSpawn;
		Ref<EnemyManager>	  m_EnemyManager;

		void spawnEnemies();
	};
}


