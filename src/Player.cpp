#include "pch.h"
#include "Player.h"
// -----------------------------------------
#include "CollisionManager.h"
#include "Constants.h"
#include "Enemy.h"
#include "Wave.h"
// -----------------------------------------
namespace lpa
{
	using namespace Constants;
	/**
	 * Función utilitaria, utilizada para comparar pares de valores y obtener
	 * el enemigo con el máximo valor en el eje y. 
	 * Al momento de atacar se almacenan los enemigos atacables en un diccionario,
	 * utilizando como valor el eje y se logra atacar al enemigo visible y no al solapado.
	 */
	typedef std::map<Enemy*, float> pair;
	bool comparePositionY(pair::value_type pos1, pair::value_type pos2)
	{
		return (pos1 < pos2);
	}
	// -----------------------------------------
	Player::Player()
		: m_attackablesEnemies{}
		, m_axeSoundBuffer{}
		, m_axeSound{}
		, m_speedAttack { sf::seconds(0.5f) }
		, m_attacking { false }
		, m_moving { false }
		, m_rangeAttack {}
	{
		setupAnimations();
		m_animatedSprite.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);
		m_animatedSpriteBlood.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);
		resetPosition();

		m_health = 500.f;
		m_maxHealth = m_health;
		m_alive = true;
		m_active = true;
		m_timeSinceLastAttack = m_clockAttack.restart();
		m_deadTime = sf::seconds(2.f);
		m_elapsedDeadTime = sf::seconds(0.f);

		m_axeSoundBuffer.loadFromFile(Constants::battleAxeSwingSound);
		m_axeSound.setBuffer(m_axeSoundBuffer);
	}
	void Player::setupAnimations()
	{
		// IDLE
		m_textureIdle.loadFromFile(texturePlayerIdleAnimation);
		m_idleAnimation.setSpriteSheet(m_textureIdle);

		m_idleAnimation.addFrame(sf::IntRect(0, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(123, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(246, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(369, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(492, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(615, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(738, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(861, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(984, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(1107, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(1230, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(1353, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(1476, 0, 123, 122));
		m_idleAnimation.addFrame(sf::IntRect(1599, 0, 123, 122));

		// WALK
		m_textureWalk.loadFromFile(texturePlayerWalkAnimation);
		m_walkingAnimation.setSpriteSheet(m_textureWalk);

		m_walkingAnimation.addFrame(sf::IntRect(0, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(127, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(254, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(381, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(508, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(635, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(762, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(889, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(1016, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(1143, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(1270, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(1397, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(1524, 0, 127, 122));
		m_walkingAnimation.addFrame(sf::IntRect(1651, 0, 127, 122));

		// ATTACK
		m_textureAttack.loadFromFile(texturePlayerAttackAnimation);
		m_attackAnimation.setSpriteSheet(m_textureAttack);

		m_attackAnimation.addFrame(sf::IntRect(0, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(139, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(278, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(417, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(556, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(695, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(834, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(973, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(1112, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(1251, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(1390, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(1529, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(1668, 0, 139, 122));
		m_attackAnimation.addFrame(sf::IntRect(1807, 0, 139, 122));

		// HURT
		m_textureHurt.loadFromFile(texturePlayerHurtAnimation);
		m_hurtAnimation.setSpriteSheet(m_textureHurt);
		
		m_hurtAnimation.addFrame(sf::IntRect(0, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(140, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(280, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(420, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(560, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(700, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(840, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(980, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(1120, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(1260, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(1400, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(1540, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(1680, 0, 140, 122));
		m_hurtAnimation.addFrame(sf::IntRect(1820, 0, 140, 122));

		// DIE
		m_textureDie.loadFromFile(texturePlayerDieAnimation);
		m_dieAnimation.setSpriteSheet(m_textureDie);
		
		m_dieAnimation.addFrame(sf::IntRect(2158, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(0, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(166, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(332, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(498, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(664, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(830, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(996, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(1162, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(1328, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(1494, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(1660, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(1826, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(1992, 0, 166, 122));
		m_dieAnimation.addFrame(sf::IntRect(2158, 0, 166, 122));
		
		m_currentAnimation = m_idleAnimation;
		m_animatedSprite.setAnimation(*m_currentAnimation);

		// RED BLOOD
		m_redBloodTexture.loadFromFile(Constants::texturePathRedBlood);
		m_bloodAnimation.setSpriteSheet(m_redBloodTexture);
		
		m_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(0, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(128, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(256, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(384, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(512, 0, 128, 128));
		m_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));
		
		m_animatedSpriteBlood.setAnimation(m_bloodAnimation);
	}
	void Player::handlerInputs()
	{
		if (!m_active) return;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
			sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			moveLeft();
		}
		else
		{
			stopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			moveRigth();
		}
		else
		{
			stopRigth();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			moveUp();
		}
		else
		{
			stopUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			moveDown();
		}
		else
		{
			stopDown();
		}
	}
	void Player::handlerInputsAttack(Wave& wave, const sf::RenderWindow& window)
	{
		if (!m_active) return;
		// TODO - Para atacar con una tecla hay que tener en cuenta la dirección donde está pegando,
		// sino le puede pegar a otros que están en la lista de atacables
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_attacking = true;

			m_currentAnimation = m_attackAnimation;
			m_animatedSprite.play(*m_currentAnimation);
			m_axeSound.play();
		}
		else
		{
			m_attacking = false;
		}

		if (m_attacking)
		{
			sf::Vector2i targetCoords = sf::Mouse::getPosition(window);
			auto maxWaveEnemies { wave.getMaxEnemies() };

			std::map<Enemy*, float> tempEnemyDictionary;
			for (uint i = 0; i < maxWaveEnemies; i++)
			{
				auto& enemy = wave.getEnemyRefByIndex(i);
				if (enemy.isAlive())
				{
					if (enemy.getAnimatedSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(targetCoords)))
					{
						//std::cout << "Attack with mouse, Coordinates: x: " << targetCoords.x << " - y: " << targetCoords.y << std::endl;
						// Verifica si está en la lista de enemigos atacables (se incluyen por estar en rango de ataque)
						if (isItemAttackablesEnemiesList(enemy))
						{
							tempEnemyDictionary.insert(std::make_pair(&enemy, enemy.getPosition().y));
						}
					}
				}
			}
			// Ordena los items por la posición en el eje y, y toma el mayor valor
			// Para eliminar primero a los enemigos de la capa superior
			if (!tempEnemyDictionary.empty())
			{
				auto it = std::max_element(tempEnemyDictionary.begin(), tempEnemyDictionary.end(), comparePositionY);
				attack(*it->first);
			}
		}
	}
	void Player::update(sf::Time elapsedTime)
	{
		if (m_active)
		{
			move(elapsedTime);
			calculateDirection();
			rotateSprite();
		}

		verifyDeath(elapsedTime);

		setAttributesAnimations();
		m_animatedSprite.update(elapsedTime);
		m_animatedSpriteBlood.update(elapsedTime);
	}
	void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_animatedSprite);
	}
	void Player::resetPosition()
	{
		m_position.x = k_WindowWidth * 0.5f;
		m_position.y = k_WindowHeight * 0.5f + m_animatedSprite.getGlobalBounds().height;
		m_animatedSprite.setPosition(m_position);
	}
	void Player::attack(Enemy& enemy)
	{
		m_timeSinceLastAttack = m_clockAttack.getElapsedTime();
		if (m_timeSinceLastAttack > m_speedAttack)
		{
			enemy.takeDamage(calculateDamage());
			m_attacking = false;

			m_clockAttack.restart();
		}
	}
	void Player::move(sf::Time elapsedTime)
	{
		m_prevPosition = m_position;

		if (m_upPressed)	m_position.y -= m_velocity * elapsedTime.asSeconds();
		if (m_downPressed)	m_position.y += m_velocity * elapsedTime.asSeconds();
		if (m_rightPressed)	m_position.x += m_velocity * elapsedTime.asSeconds();
		if (m_leftPressed)	m_position.x -= m_velocity * elapsedTime.asSeconds();

		m_animatedSprite.setPosition(m_position);
		m_animatedSpriteBlood.setPosition(m_position.x, m_position.y + 5.f);

		if (m_upPressed || m_downPressed || m_rightPressed || m_leftPressed)
		{
			m_moving = true;
			m_currentAnimation = m_walkingAnimation;
			m_animatedSprite.play(*m_currentAnimation);
		}
		else
		{
			m_moving = false;
			auto& currentAnimation{ m_currentAnimation.value().get() };
			if (&currentAnimation == &m_walkingAnimation)
			{
				m_animatedSprite.stop();
			}

			if (!m_animatedSprite.isPlaying())
			{
				m_currentAnimation = m_idleAnimation;
				m_animatedSprite.play(*m_currentAnimation);
			}	
		}
	}
	void Player::movePreviousPosition()
	{
		m_position = m_prevPosition;
		m_animatedSprite.setPosition(m_position);
		m_animatedSpriteBlood.setPosition(m_position.x, m_position.y + 5.f);
	}
	uint Player::calculateDamage()
	{
		return	m_strength;
	}
	void Player::takeDamage(uint damage)
	{
		m_health -= damage;
		if (m_health <= 0)
		{
			m_health = 0;
			return;
		}
		std::cout << "Player Health: " << m_health << std::endl;

		m_currentAnimation = m_hurtAnimation;
		m_animatedSprite.play(*m_currentAnimation);
		m_animatedSpriteBlood.play();
	}
	void Player::verifyDeath(sf::Time elapsedTime)
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
			}

			m_elapsedDeadTime += elapsedTime;
			if (m_elapsedDeadTime > m_deadTime)
			{
				m_alive = false;
				std::cout << "Player Died" << std::endl;
			}
		}
	}
	void Player::addAttackableEnemy(Enemy& enemy)
	{
		if (isItemAttackablesEnemiesList(enemy))
			return;

		m_attackablesEnemies.emplace_back(std::ref(enemy));
	}
	void Player::removeAttackableEnemy(Enemy& enemy)
	{
		if (!isItemAttackablesEnemiesList(enemy)) return;
		
		m_attackablesEnemies.remove_if(
				[&](const auto& enemyInContainer) { return &enemyInContainer.get() == &enemy; }
		);
	}
	bool Player::isItemAttackablesEnemiesList(const Enemy& enemy)
	{
		auto it = std::find_if(m_attackablesEnemies.begin(), m_attackablesEnemies.end(),
			[&](const auto& enemyInContainer) { return &enemyInContainer.get() == &enemy; });
		
		if (it != m_attackablesEnemies.end())
			return true;
		
		return false;
	}
	void Player::setAttributesAnimations()
	{
		auto& currentAnimation{ m_currentAnimation.value().get() };
		if	(&currentAnimation == &m_idleAnimation)
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
