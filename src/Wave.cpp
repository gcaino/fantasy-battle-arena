#include "pch.h"
#include "Wave.h"
// -----------------------------------------
#include "Player.h"
// -----------------------------------------
namespace lpa
{
	Wave::Wave()
		: m_enemies {}
		, m_remainingEnemies { k_MaxEnemies }
		, m_indexCurrentEnemy { 0 }
	{
	}
	void Wave::update(sf::Time elapsedTime, Player* pPlayer)
	{
		for (auto& enemy : m_enemies)
		{
			if (enemy.isAlive())
				enemy.update(elapsedTime, pPlayer);
		}
	}
	void Wave::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& enemy : m_enemies)
		{
			if (enemy.isAlive())
				enemy.draw(target, states);
		}
	}
}
