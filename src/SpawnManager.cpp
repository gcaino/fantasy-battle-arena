#include "SpawnManager.h"
// -----------------------------------------
#include "Constants.h"
#include "Wave.h"
#include <cstdlib>
#include <iostream>
// -----------------------------------------
using namespace Constants;
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
SpawnManager::SpawnManager(Wave* wave)
	: SPAWN_POINT_UNO(0, WINDOW_HEIGHT_MAX * 0.75f)
	, SPAWN_POINT_DOS(WINDOW_WIDTH_MAX - 100, WINDOW_HEIGHT_MAX * 0.75f)
	, SPAWN_POINTS_MAX(2)
	, SPAWN_TIME(sf::seconds(10.f))
	, _spawnPoints{ SPAWN_POINT_UNO, SPAWN_POINT_DOS }
	, _spawnTime(SPAWN_TIME)
	, _timeSinceLastSpawn(sf::seconds(0.f))
	, _wave(wave)
{
	//std::cout << _wave << std::endl;
}
SpawnManager::~SpawnManager()
{
	//std::cout << "Destroy SpawnManager" << std::endl;
}
void SpawnManager::update(sf::Time elapsedTime)
{
	_timeSinceLastSpawn += elapsedTime;
	if (_timeSinceLastSpawn >= _spawnTime)
	{
		spawnEnemies();
		_timeSinceLastSpawn = sf::seconds(0.f);
	}
}
void SpawnManager::spawnEnemies()
{
	if (_wave->getRemainingEnemies() > 0)
	{
		uint randomPoint = std::rand() % SPAWN_POINTS_MAX;
		uint indexCurrentEnemy = _wave->getIndexCurrentEnemy();

		Enemy* currentEnemy = &_wave->getEnemyRefByIndex(indexCurrentEnemy);
		currentEnemy->setAlive(true);
		currentEnemy->setActive(true);
		currentEnemy->setPosition(_spawnPoints[randomPoint]);

		_wave->increaseIndexCurrentEnemy();
		_wave->decreaseRemainingEnemies();

		std::cout << "Spawn Enemy" << std::endl;
	}
}
// -----------------------------------------
}
