#include "pch.h"
#include "Enemy.h"
// -----------------------------------------
#include "AnimatedSprite.h"
#include "Player.h"
#include "AssetManager.h"
#include "AnimationManager.h"
// -----------------------------------------
namespace lpa
{
	Enemy::Enemy()
		: m_movCmp{}
		, m_speedAttack(sf::seconds(3.f))
		, m_points(10)
		, m_following(true)
		, m_rangeAttack(false)
		, m_timeToFollow(sf::seconds(2.f))
		, m_timeSinceNotFollowing(sf::seconds(0.f))
		, m_clockFollowingActive(false)
		, m_waiting(false)
		, m_waitTime(sf::seconds(5.f))
		, m_elapsedWaitTime(sf::Time::Zero)
		, m_orcAttackSound{}
		, m_orcDieSound{}
	{
	}
	void Enemy::initialize()
	{
		m_movCmp.velocity = 20.f;
		m_movCmp.currentDirection.xAxis = AxisDirection::Right;
		m_movCmp.prevDirection.xAxis	= AxisDirection::Right;

		m_currentAnimation = AnimationManager::getAnimationByKey("orc-idle");
		m_animatedSprite.setAnimation(*m_currentAnimation);
		m_animatedSprite.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);
		m_animatedSprite.setScale(1.5f, 1.5f);

		m_animatedSpriteBlood.setAnimation(AnimationManager::getAnimationByKey("green-blood"));
		m_animatedSpriteBlood.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);

		m_timeSinceLastAttack = m_clockAttack.restart();
		m_deadTime = sf::seconds(10.f);
		m_elapsedDeadTime = sf::seconds(0.f);

		m_orcAttackSound.setBuffer(AssetManager<sf::SoundBuffer>::GetAssetByKey("orc-attack-sound"));
		m_orcAttackSound.setVolume(80.f);

		m_orcDieSound.setBuffer(AssetManager<sf::SoundBuffer>::GetAssetByKey("orc-die-sound"));
		m_orcDieSound.setVolume(80.f);
	}

	void Enemy::update(sf::Time elapsedTime, Player& player)
	{
		if (!player.isAlive()) return;

		if (m_active)
		{
			m_movCmp.prevPosition = m_movCmp.position;
			m_movCmp.setPreviousDirection();
			move(elapsedTime, player);
			m_movCmp.calculateDirection();
			rotateSprite();
			waiting(elapsedTime);
		}
		verifyDeath(elapsedTime, player);

		setAttributesAnimations();
		m_animatedSprite.update(elapsedTime);
		m_animatedSpriteBlood.update(elapsedTime);
	}

	void Enemy::move(sf::Time elapsedTime, const Player& player)
	{
		if (!player.isAlive()) return;

		if (!m_waiting)
		{
			auto& currentAnimation{ m_currentAnimation.value().get() };
			if ((&currentAnimation == &AnimationManager::getAnimationByKey("orc-hurt")) && m_animatedSprite.isPlaying())
				return;

			if ((&currentAnimation == &AnimationManager::getAnimationByKey("orc-idle")) && m_animatedSprite.isPlaying())
				m_animatedSprite.stop();

			auto& position = m_movCmp.position;
			auto velocity = m_movCmp.velocity;
			auto posPlayer = player.getMovCmp().position;
			
			if (posPlayer.x > position.x)
				position.x += velocity * elapsedTime.asSeconds();
			else if (posPlayer.x < position.x)
				position.x -= velocity * elapsedTime.asSeconds();
			
			if (posPlayer.y > position.y)
				position.y += velocity * elapsedTime.asSeconds();
			else if (posPlayer.y < position.y)
				position.y -= velocity * elapsedTime.asSeconds();

			m_animatedSprite.setPosition(position);

			if (!m_animatedSprite.isPlaying())
			{
				m_currentAnimation = AnimationManager::getAnimationByKey("orc-walk");
				m_animatedSprite.play(*m_currentAnimation);
			}
		}
		else
		{
			if (!m_animatedSprite.isPlaying())
			{
				m_currentAnimation = AnimationManager::getAnimationByKey("orc-idle");
				m_animatedSprite.play(*m_currentAnimation);
			}
		}
}

void Enemy::movePreviousPosition()
{
	m_movCmp.position = m_movCmp.prevPosition;
	m_animatedSprite.setPosition(m_movCmp.position);
}

void Enemy::rotateSprite()
{
	if (m_movCmp.currentDirection.xAxis != m_movCmp.prevDirection.xAxis)
	{
		m_animatedSprite.scale(-1, 1);
	}
}

void Enemy::waitToFollow(sf::Time elapsedTime)
{
	m_timeSinceNotFollowing += elapsedTime;
	if (m_timeSinceNotFollowing > m_timeToFollow)
	{
		m_following = true;
		m_clockFollowingActive = false;
		m_timeSinceNotFollowing = sf::Time::Zero;
	}
}
void Enemy::restartClockToFollow()
{
	m_clockFollowing.restart();
	m_clockFollowingActive = true;
}

void Enemy::waiting(sf::Time elapsedTime)
{
	m_elapsedWaitTime += elapsedTime;
	if (m_elapsedWaitTime >= m_waitTime)
	{
		m_waiting = false;
		m_elapsedWaitTime = sf::Time::Zero;
	}
}

void Enemy::attack(Player& player)
{
	m_timeSinceLastAttack = m_clockAttack.getElapsedTime();
	if (m_timeSinceLastAttack > m_speedAttack)
	{
		m_orcAttackSound.play();

		//std::cout << "Enemy Attack" << std::endl;
		player.takeDamage(calculateDamage());

		m_currentAnimation = AnimationManager::getAnimationByKey("orc-attack");
		m_animatedSprite.play(*m_currentAnimation);

		m_waiting = true;
		m_clockAttack.restart();
	}
}

void Enemy::takeDamage(unsigned int damage)
{
	m_health -= damage;
	//std::cout << "Enemy Health: " << m_health << std::endl;
	if (m_health <= 0)
	{
		m_health = 0;
		return;
	}

	m_currentAnimation = AnimationManager::getAnimationByKey("orc-hurt");
	m_animatedSprite.play(*m_currentAnimation);
	
	m_animatedSpriteBlood.setPosition(m_movCmp.position.x, m_movCmp.position.y);
	m_animatedSpriteBlood.play();
}

uint Enemy::calculateDamage()
{
	return	m_strength;
}

void Enemy::verifyDeath(sf::Time elapsedTime, Player& player)
{
	if (m_health <= 0)
	{
		auto& currentAnimation{ m_currentAnimation.value().get() };
		if (m_active && (&currentAnimation != &AnimationManager::getAnimationByKey("orc-die")))
		{
			m_animatedSprite.pause();
			m_currentAnimation = AnimationManager::getAnimationByKey("orc-die");
			m_animatedSprite.play(*m_currentAnimation);
			m_animatedSprite.setFrame(1);
			m_active = false;
			player.addEnemyKilled();
			m_orcDieSound.play();
		}

		m_elapsedDeadTime += elapsedTime;
		if (m_elapsedDeadTime > m_deadTime)
		{
			m_alive = false;
			//std::cout << "Enemy Died" << std::endl;
		}
	}
}

void Enemy::setAttributesAnimations()
{
	auto& currentAnimation{ m_currentAnimation.value().get() };
	if (&currentAnimation == &AnimationManager::getAnimationByKey("orc-idle"))
	{
		m_animatedSprite.setFrameTime(sf::seconds(0.2f));
	}
	else if (&currentAnimation == &AnimationManager::getAnimationByKey("orc-attack"))
	{
		m_animatedSprite.setFrameTime(sf::seconds(0.05f));
	}
	else
	{
		m_animatedSprite.setFrameTime(sf::seconds(0.1f));
	}
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_animatedSprite);
}
}
