#pragma once
// -----------------------------------------
#include "pch.h"
#include "ecs/Entity.h"
#include "AnimatedSprite.h"
// -----------------------------------------
namespace lpa
{
	class MovementCmp;
	class StatCmp;
	class Player;
	// -------------------------------------
	class Enemy : public Entity
	{
	public:
		Enemy();

		AnimatedSprite	getAnimatedSprite() const		{ return m_animatedSprite; }
		AnimatedSprite	getAnimatedSpriteBlood() const	{ return m_animatedSpriteBlood; }

		void initialize();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		bool isFollowing() const			{ return m_following; }
		void setFollowing(bool following)	{ m_following = following; }
		bool isClockFollowingActive() const { return m_clockFollowingActive; }
	
		void update(sf::Time elapsedTime, Player& player);
		void movePreviousPosition();
		void rotateSprite();
		void waitToFollow(sf::Time elapsedTime);
		void restartClockToFollow();
		void attack(Player& player);
		void takeDamage(unsigned int damage);

	private:
		void waiting(sf::Time elapsedTime);
		void setAttributesAnimations();
		void move(sf::Time elapsedTime, const Player& player);
		uint calculateDamage();
		void verifyDeath(sf::Time elapsedTime, Player& player);

		MovementCmp&	m_movCmp;
		StatCmp&		m_statCmp;

		std::optional<Ref<Animation>>	m_currentAnimation;
		AnimatedSprite					m_animatedSprite;
		AnimatedSprite					m_animatedSpriteBlood;
		Animation						m_bloodAnimation;

		uint				m_points;
		bool				m_following;					
		float				m_rangeAttack;

		sf::Time			m_speedAttack;
		sf::Time			m_timeSinceLastAttack;
		sf::Clock			m_clockAttack;
				
		sf::Time			m_deadTime;
		sf::Time			m_elapsedDeadTime;
		sf::Time			m_timeToFollow;
		sf::Time			m_timeSinceNotFollowing;
		sf::Clock			m_clockFollowing;
		bool				m_clockFollowingActive;
		sf::Time			m_waitTime;
		sf::Time			m_elapsedWaitTime;
		bool				m_waiting;
							
		sf::Sound			m_orcAttackSound;
		sf::Sound			m_orcDieSound;
	};
}

