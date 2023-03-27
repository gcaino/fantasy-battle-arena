#include "pch.h"
#include "Enemy.h"
// -----------------------------------------
#include "AnimatedSprite.h"
#include "Player.h"
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
	{
		setupAnimations();
		m_animatedSprite.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);
		m_animatedSpriteBlood.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);

		m_timeSinceLastAttack = m_clockAttack.restart();
		m_deadTime = sf::seconds(10.f);
		m_elapsedDeadTime = sf::seconds(0.f);

		m_orcAttackSoundBuffer.loadFromFile(Constants::orcAttackSound);
		m_orcAttackSound.setBuffer(m_orcAttackSoundBuffer);
		m_orcAttackSound.setVolume(80.f);
		m_orcDieSoundBuffer.loadFromFile(Constants::orcDieSound);
		m_orcDieSound.setBuffer(m_orcDieSoundBuffer);
		m_orcDieSound.setVolume(80.f);
	}
	void Enemy::setupAnimations()
	{
		// IDLE
		m_textureIdle.loadFromFile(textureOrcIdleAnimation);
		m_idleAnimation.setSpriteSheet(m_textureIdle);

		m_idleAnimation.addFrame(sf::IntRect(0, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(158, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(316, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(474, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(632, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(790, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(948, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(1106, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(1264, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(1422, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(1580, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(1738, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(1896, 0, 158, 155));
		m_idleAnimation.addFrame(sf::IntRect(2054, 0, 158, 155));

		// WALK
		m_textureWalk.loadFromFile(textureOrcWalkAnimation);
		m_walkingAnimation.setSpriteSheet(m_textureWalk);

		m_walkingAnimation.addFrame(sf::IntRect(0, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(161, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(322, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(483, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(644, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(805, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(966, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(1127, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(1288, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(1449, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(1610, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(1771, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(1932, 0, 161, 155));
		m_walkingAnimation.addFrame(sf::IntRect(2093, 0, 161, 155));

		// ATTACK
		m_textureAttack.loadFromFile(textureOrcAttackAnimation);
		m_attackAnimation.setSpriteSheet(m_textureAttack);

		m_attackAnimation.addFrame(sf::IntRect(0, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(177, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(354, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(531, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(708, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(885, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(1062, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(1239, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(1416, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(1593, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(1770, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(1947, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(2124, 0, 177, 155));
		m_attackAnimation.addFrame(sf::IntRect(2301, 0, 177, 155));

		// HURT
		m_textureHurt.loadFromFile(textureOrcHurtAnimation);
		m_hurtAnimation.setSpriteSheet(m_textureHurt);

		m_hurtAnimation.addFrame(sf::IntRect(0, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(153, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(306, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(459, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(612, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(765, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(918, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(1071, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(1224, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(1377, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(1530, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(1683, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(1836, 0, 153, 155));
		m_hurtAnimation.addFrame(sf::IntRect(1989, 0, 153, 155));

		// DIE
		m_textureDie.loadFromFile(textureOrcDieAnimation);
		m_dieAnimation.setSpriteSheet(m_textureDie);

		m_dieAnimation.addFrame(sf::IntRect(2860, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(0, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(220, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(440, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(660, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(880, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(1100, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(1320, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(1540, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(1760, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(1980, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(2200, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(2420, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(2640, 0, 220, 155));
		m_dieAnimation.addFrame(sf::IntRect(2860, 0, 220, 155));

		m_currentAnimation = m_idleAnimation;
		m_animatedSprite.setAnimation(*m_currentAnimation);

		// GREEN BLOOD
		m_greenBloodTexture.loadFromFile(Constants::texturePathGreenBlood);
		m_bloodAnimation.setSpriteSheet(m_greenBloodTexture);

		m_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(0, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(128, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(256, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(384, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(512, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));

		m_animatedSpriteBlood.setAnimation(m_bloodAnimation);
	}
	void Enemy::update(sf::Time elapsedTime, Player& player)
	{
		if (!player.isAlive()) return;

		if (m_active)
		{
			move(elapsedTime, player);
			calculateDirection();
			rotateSprite();
			waiting(elapsedTime);
		}
		verifyDeath(elapsedTime, player);

		setAttributesAnimations();
		m_animatedSprite.update(elapsedTime);
		m_animatedSpriteBlood.update(elapsedTime);
	}
	void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_animatedSprite);
	}
	void Enemy::move(sf::Time elapsedTime, const Player& player)
	{
		if (player.isAlive())
		{
			if (!m_waiting)
			{
				auto& currentAnimation{ m_currentAnimation.value().get() };
				if ((&currentAnimation == &m_hurtAnimation) && m_animatedSprite.isPlaying()) 
					return;

				if ((&currentAnimation == &m_idleAnimation) && m_animatedSprite.isPlaying()) 
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
					m_currentAnimation = m_walkingAnimation;
					m_animatedSprite.play(*m_currentAnimation);
				}
			}
			else
			{
				if (!m_animatedSprite.isPlaying())
				{
					m_currentAnimation = m_idleAnimation;
					m_animatedSprite.play(*m_currentAnimation);
				}
			}
		}
	}
	void Enemy::movePreviousPosition()
	{
		m_position = m_prevPosition;
		m_animatedSprite.setPosition(m_position);
		m_animatedSpriteBlood.setPosition(m_position.x, m_position.y);
	}
	void Enemy::moveRandomDirection()
	{
		// TODO método para evitar que los enemigos se queden atorados en el mapa
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
			m_currentAnimation = m_attackAnimation;
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

		m_currentAnimation = m_hurtAnimation;
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
			if (m_active && (&currentAnimation != &m_dieAnimation))
			{
				m_animatedSprite.pause();
				m_currentAnimation = m_dieAnimation;
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
		if (&currentAnimation == &m_idleAnimation)
		{
			m_animatedSprite.setFrameTime(sf::seconds(0.2f));
		}
		else if (&currentAnimation == &m_attackAnimation || &currentAnimation == &m_hurtAnimation)
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
}
