#pragma once
// -----------------------------------------
#include "pch.h"
#include "entities\Entity.h"
#include "cmp\KeyboardInputCmp.h"
#include "cmp\MovementCmp.h"
#include "cmp\StatCmp.h"
#include "Animation.h"
#include "AnimatedSprite.h"
// -----------------------------------------
namespace lpa
{
	class Enemy;
	class EnemyManager;
	// -----------------------------------------
	class Player : public Entity
	{
	public:
		Player();

		StatCmp& getStatCmp()				{ return m_statCmp; };
		const StatCmp& getStatCmp() const	{ return m_statCmp; };

		AnimatedSprite	getAnimatedSprite() const		{ return m_animatedSprite; }
		AnimatedSprite	getAnimatedSpriteBlood() const	{ return m_animatedSpriteBlood; }

		void initialize();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		const MovementCmp& getMovCmp() const { return m_movCmp; };

		bool isAttacking() const { return m_attacking; }
		void setAttacking(bool attacking) { m_attacking = attacking; }
		bool isMoving() const { return m_moving; }
		void setMoving(bool moving) { m_moving = moving; }
		uint getEnemiesKilled() const { return m_enemiesKilled; }
		void addEnemyKilled() { ++m_enemiesKilled; }

		void addAttackableEnemy(Enemy& enemy);
		void removeAttackableEnemy(Enemy& enemy);
		bool isItemAttackablesEnemiesList(const Enemy& enemy);

		void handlerInputsAttack(EnemyManager& EnemyManager, const sf::RenderWindow& window);

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
		void rotateSprite();

		std::list<Ref<Enemy>>	m_attackablesEnemies;
		KeyboardInputCmp		m_keyboardInputCmp;
		MovementCmp				m_movCmp;
		StatCmp					m_statCmp;

		std::optional<Ref<Animation>>	m_currentAnimation;
		AnimatedSprite					m_animatedSprite;
		AnimatedSprite					m_animatedSpriteBlood;
		Animation						m_bloodAnimation;

		sf::Sound			m_axeSound;

		sf::Time			m_deadTime;
		sf::Time			m_elapsedDeadTime;
		sf::Time			m_speedAttack;
		sf::Time			m_timeSinceLastAttack;
		sf::Clock			m_clockAttack;
		bool				m_attacking;
		bool				m_moving;
		float				m_rangeAttack;
		uint				m_enemiesKilled;
	};
}

