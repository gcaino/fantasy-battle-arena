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
	using namespace Constants;

	Enemy::Enemy()
		: m_velocity(20.f)
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
		m_currentAnimation = AnimationManager::getAnimationByKey("orc-idle");
		m_animatedSprite.setAnimation(*m_currentAnimation);
		m_animatedSprite.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);

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
			move(elapsedTime, player);
			calculateDirection();
			rotateSprite();
			setPreviousDirection();
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

			m_prevPosition = m_position;

			sf::Vector2f posPlayer = player.getPosition();
			if (posPlayer.x > m_position.x)
				m_position.x += m_velocity * elapsedTime.asSeconds();
			if (posPlayer.x < m_position.x)
				m_position.x -= m_velocity * elapsedTime.asSeconds();
			if (posPlayer.y > m_position.y)
				m_position.y += m_velocity * elapsedTime.asSeconds();
			if (posPlayer.y < m_position.y)
				m_position.y -= m_velocity * elapsedTime.asSeconds();

			m_animatedSprite.setPosition(m_position);
			m_animatedSpriteBlood.setPosition(m_position.x, m_position.y);

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
	m_position = m_prevPosition;
	m_animatedSprite.setPosition(m_position);
	m_animatedSpriteBlood.setPosition(m_position.x, m_position.y);
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
		//std::cout << "Enemy Attack" << std::endl;
		player.takeDamage(calculateDamage());

		m_orcAttackSound.play();
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
	else if (&currentAnimation == &AnimationManager::getAnimationByKey("orc-attack") ||
		&currentAnimation == &AnimationManager::getAnimationByKey("orc-hurt"))
	{
		m_animatedSprite.setFrameTime(sf::seconds(0.05f));
	}
	else
	{
		m_animatedSprite.setFrameTime(sf::seconds(0.1f));
	}

	if (m_animatedSpriteBlood.isPlaying())
	{
		m_drawBlood = true;
	}
	else
	{
		m_drawBlood = false;
	}
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_animatedSprite);
}
}
