#pragma once
// -----------------------------------------
#include "pch.h"
#include "Character.h"
#include "GameObject.h"
// -----------------------------------------
namespace lpa
{
	class Player;
	// -----------------------------------------
	class Enemy : public Character
	{
	public:
		Enemy();

		bool isFollowing() const			{ return m_following; }
		void setFollowing(bool following)	{ m_following = following; }
		bool isClockFollowingActive() const { return m_clockFollowingActive; }
		void addAttackablePlayer(Player* enemy);
		void removeAttackablePlayer(Player* enemy);
	
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time elapsedTime, Player* pPlayer);
		void movePreviousPosition();
		void moveRandomDirection();
		void waitToFollow(sf::Time elapsedTime);
		void restartClockToFollow();
		void attack(Player* pPlayer);
		void takeDamage(unsigned int damage);
		//void die();

	private:
		void waiting(sf::Time elapsedTime);
		void setupAnimations();
		void setAttributesAnimations();
		void move(sf::Time elapsedTime, Player* pPlayer);
		uint calculateDamage();
		void verifyDeath(sf::Time elapsedTime, Player& player);
		void iteratePlayersAttackables(Player* pPlayer);
		bool isItemAttackablesPlayersList(Player* pPlayer);

		float				m_velocity;

		uint				m_points;
		bool				m_following;
							
		float				m_rangeAttack;
		std::list<Player*>	m_attackablesPlayers;
		std::list<Player*>::iterator it;

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
							
		sf::SoundBuffer		m_orcAttackSoundBuffer;
		sf::SoundBuffer		m_orcDieSoundBuffer;
		sf::Sound			m_orcAttackSound;
		sf::Sound			m_orcDieSound;
	};
}

