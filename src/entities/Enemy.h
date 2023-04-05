#pragma once
// -----------------------------------------
#include "pch.h"
#include "Character.h"
#include "cmp\MovementCmp.h"
// -----------------------------------------
namespace lpa
{
	class Player;
	// -------------------------------------
	class Enemy : public Character
	{
	public:
		Enemy();

		MovementCmp& getMovCmp() { return m_movCmp; };

		void initialize() override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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

		MovementCmp			m_movCmp;

		uint				m_points;
		bool				m_following;					
		float				m_rangeAttack;

		sf::Time			m_speedAttack;
		sf::Time			m_timeSinceLastAttack;
		sf::Clock			m_clockAttack;
							
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

