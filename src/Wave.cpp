#include "Wave.h"
// -----------------------------------------
#include "Player.h"
#include <iostream>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
Wave::Wave()
	: _maxEnemies(ENEMY_MAX)
	, _remainingEnemies(ENEMY_MAX)
	, _indexCurrentEnemy(0)
{
}
Wave::~Wave()
{
	//std::cout << "Destroy Wave" << std::endl;
}
void Wave::update(sf::Time elapsedTime, Player* pPlayer)
{
	for (uint i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemies[i].isAlive())
		{
			_enemies[i].update(elapsedTime, pPlayer);
		}
	}
}
void Wave::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (uint i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemies[i].isAlive())
			_enemies[i].draw(target, states);
	}
}
// -----------------------------------------
}
