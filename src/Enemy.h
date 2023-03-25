#ifndef ENEMY_H
#define ENEMY_H
// -----------------------------------------
#include "Character.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <list>
#include <iterator>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
// -----------------------------------------
class Player;
// -----------------------------------------
class Enemy : public Character
{
private:
	const float			ENEMY_VELOCITY;
	const sf::Time		ENEMY_SPEED_ATTACK;

	uint				_points;
	bool				_following;

	float				_rangeAttack;
	std::list<Player*>	_attackablesPlayers;
	std::list<Player*>::iterator it;

	sf::Time			_speedAttack;
	sf::Time			_timeSinceLastAttack;
	sf::Clock			_clockAttack;

	sf::Time			_timeToFollow;
	sf::Time			_timeSinceNotFollowing;
	sf::Clock			_clockFollowing;
	bool				_clockFollowingActive;
	sf::Time			_waitTime;
	sf::Time			_elapsedWaitTime;
	bool				_waiting;

	sf::SoundBuffer		_orcAttackSoundBuffer;
	sf::SoundBuffer		_orcDieSoundBuffer;
	sf::Sound			_orcAttackSound;
	sf::Sound			_orcDieSound;

	void waiting(sf::Time elapsedTime);
	void setupAnimations();
	void setAttributesAnimations();
	void move(sf::Time elapsedTime, Player* pPlayer);
	uint calculateDamage();
	void verifyDeath(sf::Time elapsedTime, Player& player);
	void iteratePlayersAttackables(Player* pPlayer);
	bool isItemAttackablesPlayersList(Player* pPlayer);
		
public:
    Enemy();
    ~Enemy();

	bool isFollowing() const			{ return _following; }
	void setFollowing(bool following)	{ _following = following; }
	bool isClockFollowingActive() const { return _clockFollowingActive; }
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
	void die();
};
// -----------------------------------------
}
// -----------------------------------------
#endif // ENEMY_H
