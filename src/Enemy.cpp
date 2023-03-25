#include "Enemy.h"
// -----------------------------------------
#include "AnimatedSprite.h"
#include "Player.h"
#include "Constants.h"
#include <SFML\System.hpp>
#include <iostream>
#include <algorithm>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
using namespace Constants;
// -----------------------------------------
Enemy::Enemy()
	: ENEMY_VELOCITY(20.f)
	, ENEMY_SPEED_ATTACK(sf::seconds(3.f))
	, _points(10)
	, _following(true)
	, _rangeAttack(false)
	, _timeToFollow(sf::seconds(2.f))
	, _timeSinceNotFollowing(sf::seconds(0.f))
	, _clockFollowingActive(false)
	, _waiting(false)
	, _waitTime(sf::seconds(5.f))
	, _elapsedWaitTime(sf::Time::Zero)
{
	setupAnimations();
	_animatedSprite.setOrigin(_animatedSprite.getGlobalBounds().width / 2, _animatedSprite.getGlobalBounds().height);
	_animatedSpriteBlood.setOrigin(_animatedSprite.getGlobalBounds().width / 2, _animatedSprite.getGlobalBounds().height);

	_velocity = ENEMY_VELOCITY;
	_speedAttack = ENEMY_SPEED_ATTACK;
	_timeSinceLastAttack = _clockAttack.restart();
	_deadTime = sf::seconds(10.f);
	_elapsedDeadTime = sf::seconds(0.f);

	_orcAttackSoundBuffer.loadFromFile(Constants::orcAttackSound);
	_orcAttackSound.setBuffer(_orcAttackSoundBuffer);
	_orcAttackSound.setVolume(80.f);
	_orcDieSoundBuffer.loadFromFile(Constants::orcDieSound);
	_orcDieSound.setBuffer(_orcDieSoundBuffer);
	_orcDieSound.setVolume(80.f);

	//std::cout << "Create Enemy" << std::endl;
}
Enemy::~Enemy()
{
	//std::cout << "Destroy Enemy" << std::endl;
}
void Enemy::setupAnimations()
{
	// IDLE
	_textureIdle.loadFromFile(textureOrcIdleAnimation);
	_idleAnimation.setSpriteSheet(_textureIdle);

	_idleAnimation.addFrame(sf::IntRect(0, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(158, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(316, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(474, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(632, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(790, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(948, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(1106, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(1264, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(1422, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(1580, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(1738, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(1896, 0, 158, 155));
	_idleAnimation.addFrame(sf::IntRect(2054, 0, 158, 155));

	// WALK
	_textureWalk.loadFromFile(textureOrcWalkAnimation);
	_walkingAnimation.setSpriteSheet(_textureWalk);

	_walkingAnimation.addFrame(sf::IntRect(0, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(161, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(322, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(483, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(644, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(805, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(966, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(1127, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(1288, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(1449, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(1610, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(1771, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(1932, 0, 161, 155));
	_walkingAnimation.addFrame(sf::IntRect(2093, 0, 161, 155));

	// ATTACK
	_textureAttack.loadFromFile(textureOrcAttackAnimation);
	_attackAnimation.setSpriteSheet(_textureAttack);

	_attackAnimation.addFrame(sf::IntRect(0, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(177, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(354, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(531, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(708, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(885, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(1062, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(1239, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(1416, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(1593, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(1770, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(1947, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(2124, 0, 177, 155));
	_attackAnimation.addFrame(sf::IntRect(2301, 0, 177, 155));

	// HURT
	_textureHurt.loadFromFile(textureOrcHurtAnimation);
	_hurtAnimation.setSpriteSheet(_textureHurt);

	_hurtAnimation.addFrame(sf::IntRect(0, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(153, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(306, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(459, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(612, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(765, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(918, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(1071, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(1224, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(1377, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(1530, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(1683, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(1836, 0, 153, 155));
	_hurtAnimation.addFrame(sf::IntRect(1989, 0, 153, 155));

	// DIE
	_textureDie.loadFromFile(textureOrcDieAnimation);
	_dieAnimation.setSpriteSheet(_textureDie);

	_dieAnimation.addFrame(sf::IntRect(2860, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(0, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(220, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(440, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(660, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(880, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(1100, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(1320, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(1540, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(1760, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(1980, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(2200, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(2420, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(2640, 0, 220, 155));
	_dieAnimation.addFrame(sf::IntRect(2860, 0, 220, 155));

	_currentAnimation = &_idleAnimation;
	_animatedSprite.setAnimation(*_currentAnimation);

	// GREEN BLOOD
	_greenBloodTexture.loadFromFile(Constants::texturePathGreenBlood);
	_bloodAnimation.setSpriteSheet(_greenBloodTexture);

	_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(0, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(128, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(256, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(384, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(512, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));

	_animatedSpriteBlood.setAnimation(_bloodAnimation);
}
void Enemy::update(sf::Time elapsedTime, Player* pPlayer)
{
	if (!pPlayer->isAlive()) return;

	if (_active)
	{
		move(elapsedTime, pPlayer);
		calculateDirection();
		rotateSprite();
		iteratePlayersAttackables(pPlayer);
		waiting(elapsedTime);
	}
	verifyDeath(elapsedTime, *pPlayer);

	setAttributesAnimations();
	_animatedSprite.update(elapsedTime);
	_animatedSpriteBlood.update(elapsedTime);
}
void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_animatedSprite);
}
void Enemy::move(sf::Time elapsedTime, Player* pPlayer)
{
	if (pPlayer->isAlive())
	{
		if (!_waiting)
		{
			if ((_currentAnimation == &_hurtAnimation) && _animatedSprite.isPlaying()) 
				return;

			if ((_currentAnimation == &_idleAnimation) && _animatedSprite.isPlaying()) 
				_animatedSprite.stop();

			_prevPosition = _position;

			sf::Vector2f posPlayer = pPlayer->getPosition();
			if (posPlayer.x > _position.x)
				_position.x += _velocity * elapsedTime.asSeconds();
			if (posPlayer.x < _position.x)
				_position.x -= _velocity * elapsedTime.asSeconds();
			if (posPlayer.y > _position.y)
				_position.y += _velocity * elapsedTime.asSeconds();
			if (posPlayer.y < _position.y)
				_position.y -= _velocity * elapsedTime.asSeconds();

			_animatedSprite.setPosition(_position);
			_animatedSpriteBlood.setPosition(_position.x, _position.y);

			if (!_animatedSprite.isPlaying())
			{
				_currentAnimation = &_walkingAnimation;
				_animatedSprite.play(*_currentAnimation);
			}
		}
		else
		{
			if (!_animatedSprite.isPlaying())
			{
				_currentAnimation = &_idleAnimation;
				_animatedSprite.play(*_currentAnimation);
			}
		}
	}
}
void Enemy::movePreviousPosition()
{
	_position = _prevPosition;
	_animatedSprite.setPosition(_position);
	_animatedSpriteBlood.setPosition(_position.x, _position.y);
}
void Enemy::moveRandomDirection()
{
	// TODO método para evitar que los enemigos se queden atorados en el mapa
}
void Enemy::waitToFollow(sf::Time elapsedTime)
{
	_timeSinceNotFollowing += elapsedTime;
	if (_timeSinceNotFollowing > _timeToFollow)
	{
		_following = true;
		_clockFollowingActive = false;
		_timeSinceNotFollowing = sf::Time::Zero;
	}
}
void Enemy::restartClockToFollow()
{
	_clockFollowing.restart();
	_clockFollowingActive = true;
}

void Enemy::waiting(sf::Time elapsedTime)
{
	_elapsedWaitTime += elapsedTime;
	if (_elapsedWaitTime >= _waitTime)
	{
		_waiting = false;
		_elapsedWaitTime = sf::Time::Zero;
	}
}

void Enemy::attack(Player* pPlayer)
{
	_timeSinceLastAttack = _clockAttack.getElapsedTime();
	if (_timeSinceLastAttack > _speedAttack)
	{
		std::cout << "Enemy Attack" << std::endl;
		pPlayer->takeDamage(calculateDamage());

		_orcAttackSound.play();
		_currentAnimation = &_attackAnimation;
		_animatedSprite.play(*_currentAnimation);

		_waiting = true;
		_clockAttack.restart();
	}
}
void Enemy::takeDamage(unsigned int damage)
{
	_health -= damage;
	std::cout << "Enemy Health: " << _health << std::endl;
	if (_health <= 0)
	{
		_health = 0;
		return;
	}

	_currentAnimation = &_hurtAnimation;
	_animatedSprite.play(*_currentAnimation);
	_animatedSpriteBlood.play();
}
uint Enemy::calculateDamage()
{
	return	_strength;
}
void Enemy::verifyDeath(sf::Time elapsedTime, Player& player)
{
	if (_health <= 0)
	{
		if (_active && _currentAnimation != &_dieAnimation)
		{
			_animatedSprite.pause();
			_currentAnimation = &_dieAnimation;
			_animatedSprite.play(*_currentAnimation);
			_animatedSprite.setFrame(1);
			_active = false;
			player.addEnemyKilled();
			_orcDieSound.play();
		}

		_elapsedDeadTime += elapsedTime;
		if (_elapsedDeadTime > _deadTime)
		{
			_alive = false;
			std::cout << "Enemy Died" << std::endl;
		}
	}
}
void Enemy::addAttackablePlayer(Player* pPlayer)
{
	if (isItemAttackablesPlayersList(pPlayer))
		return;
	
	_attackablesPlayers.push_back(pPlayer);
}
void Enemy::removeAttackablePlayer(Player* pPlayer)
{
	if (isItemAttackablesPlayersList(pPlayer))
		_attackablesPlayers.remove(pPlayer);
}
bool Enemy::isItemAttackablesPlayersList(Player* pPlayer)
{
	return (std::find(_attackablesPlayers.begin(), _attackablesPlayers.end(), pPlayer) != _attackablesPlayers.end());
}
void Enemy::iteratePlayersAttackables(Player* pPlayer)
{
	if (isItemAttackablesPlayersList(pPlayer))
		attack(pPlayer);
}
void Enemy::setAttributesAnimations()
{
	if (_currentAnimation == &_idleAnimation)
	{
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
	}
	else if (_currentAnimation == &_attackAnimation || _currentAnimation == &_hurtAnimation)
	{
		_animatedSprite.setFrameTime(sf::seconds(0.05f));
	}
	else
	{
		_animatedSprite.setFrameTime(sf::seconds(0.1f));
	}

	if (_animatedSpriteBlood.isPlaying())
	{
		_drawBlood = true;
	}
	else
	{
		_drawBlood = false;
	}
}
// -----------------------------------------
}
