#pragma once
// -----------------------------------------
#include "pch.h"
#include "Character.h"
#include "GameObject.h"
#include "InputManager.h"
// -----------------------------------------
namespace lpa
{
	class Enemy;
	class Wave;
	// -----------------------------------------
	class Player : public Character, public InputManager
	{
	public:
		Player();

		bool isAttacking() const			{ return m_attacking; }
		void setAttacking(bool attacking)	{ m_attacking = attacking; }
		bool isMoving() const				{ return m_moving; }
		void setMoving(bool moving)			{ m_moving = moving; }
		uint getEnemiesKilled() const		{ return m_enemiesKilled; }
		void addEnemyKilled()				{ ++m_enemiesKilled; }

		void addAttackableEnemy(Enemy& enemy);
		void removeAttackableEnemy(Enemy& enemy);
		bool isItemAttackablesEnemiesList(const Enemy& enemy);

		void setupAnimations();

		void handlerInputs();
		void handlerInputsAttack(Wave& wave, const sf::RenderWindow& window);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time elapsedTime);
		void movePreviousPosition();
		void attack(Enemy& enemy);
		void takeDamage(uint damage);

	private:
		void move(sf::Time elapsedTime);
		void resetPosition();
		uint calculateDamage();
		void verifyDeath(sf::Time elapsedTime);
		void setAttributesAnimations();

		std::list<Ref<Enemy>>	m_attackablesEnemies;

		sf::SoundBuffer		m_axeSoundBuffer;
		sf::Sound			m_axeSound;

		sf::Time			m_speedAttack;
		sf::Time			m_timeSinceLastAttack;
		sf::Clock			m_clockAttack;
		bool				m_attacking;
		bool				m_moving;
		float				m_rangeAttack;
		uint				m_enemiesKilled;
	};
}


