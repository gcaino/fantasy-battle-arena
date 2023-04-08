#pragma once
// -----------------------------------------
#include "pch.h"
#include "game\Enemy.h"
// -----------------------------------------
namespace lpa
{
	class Player;
	// -------------------------------------
	class EnemyManager : public sf::Drawable
	{
	public:
		EnemyManager();

		Enemy&		 getEnemyRefByIndex(uint index)			{ return m_enemies[index]; }
		const Enemy& getEnemyRefByIndex(uint index) const	{ return m_enemies[index]; }
		uint	getRemainingEnemies() const		{ return m_remainingEnemies; }
		uint	getIndexCurrentEnemy() const	{ return m_indexCurrentEnemy; }
		uint	getMaxEnemies() const { return static_cast<uint>(m_enemies.size()); }

		void	increaseIndexCurrentEnemy() { ++m_indexCurrentEnemy; }
		void	decreaseRemainingEnemies()	{ if (m_remainingEnemies == 0) return; --m_remainingEnemies; }

		void initialize();
		void update(sf::Time elapsedTime, Player& player);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		static constexpr uint k_MaxEnemies{ 1 };
		using  Enemies = std::array<Enemy, k_MaxEnemies>;

		Enemies m_enemies;
		uint	m_indexCurrentEnemy;
		uint	m_remainingEnemies;
	};
}

