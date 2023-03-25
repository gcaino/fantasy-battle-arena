#ifndef SPAWN_MANAGER_H
#define SPAWN_MANAGER_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
// -----------------------------------------
class Wave;
// -----------------------------------------
class SpawnManager
{
private:
	const uint				SPAWN_POINTS_MAX;
	const sf::Vector2f		SPAWN_POINT_UNO;
	const sf::Vector2f		SPAWN_POINT_DOS;
	const sf::Time			SPAWN_TIME;

	sf::Vector2f			_spawnPoints[2];
	sf::Time				_spawnTime;
	sf::Time				_timeSinceLastSpawn;
	Wave*					_wave;

	void spawnEnemies();

public:
	SpawnManager(Wave* wave);
	~SpawnManager();

	void update(sf::Time elapsedTime);
};
// -----------------------------------------
}
// -----------------------------------------
#endif // SPAWN_MANAGER_H

