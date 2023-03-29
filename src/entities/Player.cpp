#include "pch.h"
#include "Player.h"
// -----------------------------------------
#include "systems\CollisionManager.h"
#include "Constants.h"
#include "Enemy.h"
#include "systems\EnemyManager.h"
#include "AssetManager.h"
#include "AnimationManager.h"
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
		, m_keyboardInputComponent{}
		, m_axeSound{}
		, m_speedAttack{ sf::seconds(0.5f) }
		, m_attacking{ false }
		, m_moving{ false }
		, m_rangeAttack{}
		, m_enemiesKilled{}
	{
	}
	void Player::initialize()
	{
		m_currentAnimation = AnimationManager::getAnimationByKey("knight-idle");
		m_animatedSprite.setAnimation(*m_currentAnimation);
		m_animatedSprite.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);

		m_animatedSpriteBlood.setAnimation(AnimationManager::getAnimationByKey("red-blood"));
		m_animatedSpriteBlood.setOrigin(m_animatedSprite.getGlobalBounds().width * 0.5f, m_animatedSprite.getGlobalBounds().height);
		resetPosition();

		m_health = 300.f;
		m_maxHealth = m_health;
		m_alive = true;
		m_active = true;
		m_timeSinceLastAttack = m_clockAttack.restart();
		m_deadTime = sf::seconds(2.f);
		m_elapsedDeadTime = sf::seconds(0.f);

		m_axeSound.setBuffer(AssetManager<sf::SoundBuffer>::GetAssetByKey("battle-axe-swing-sound"));

		m_keyboardInputComponent.bindKeyToAction(sf::Keyboard::W, "up");
		m_keyboardInputComponent.bindKeyToAction(sf::Keyboard::S, "down");
		m_keyboardInputComponent.bindKeyToAction(sf::Keyboard::A, "left");
		m_keyboardInputComponent.bindKeyToAction(sf::Keyboard::D, "right");

		m_keyboardInputComponent.bindActionsToCommands("up",	[this](sf::Time elapsedTime) {m_position.y -= m_velocity * elapsedTime.asSeconds(); });
		m_keyboardInputComponent.bindActionsToCommands("down",	[this](sf::Time elapsedTime) {m_position.y += m_velocity * elapsedTime.asSeconds(); });
		m_keyboardInputComponent.bindActionsToCommands("left",	[this](sf::Time elapsedTime) {m_position.x -= m_velocity * elapsedTime.asSeconds(); });
		m_keyboardInputComponent.bindActionsToCommands("right", [this](sf::Time elapsedTime) {m_position.x += m_velocity * elapsedTime.asSeconds(); });
	}

	void Player::handlerInputsAttack(EnemyManager& EnemyManager, const sf::RenderWindow& window)
	{
		if (!m_active) return;
		// TODO - Para atacar con una tecla hay que tener en cuenta la dirección donde está pegando,
		// sino le puede pegar a otros que están en la lista de atacables
		m_attacking = true;

		m_currentAnimation = AnimationManager::getAnimationByKey("knight-attack");
		m_animatedSprite.play(*m_currentAnimation);
		m_axeSound.play();

		sf::Vector2i targetCoords = sf::Mouse::getPosition(window);
		auto maxEnemyManagerEnemies{ EnemyManager.getMaxEnemies() };

		std::map<Enemy*, float> tempEnemyDictionary;
		for (uint i = 0; i < maxEnemyManagerEnemies; i++)
		{
			auto& enemy = EnemyManager.getEnemyRefByIndex(i);
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

	void Player::update(sf::Time elapsedTime)
	{
		if (m_active)
		{
			m_keyboardInputComponent.update(elapsedTime);
			move(elapsedTime);
		}

		verifyDeath(elapsedTime);

		setAttributesAnimations();
		m_animatedSprite.update(elapsedTime);
		m_animatedSpriteBlood.update(elapsedTime);
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
		if (m_prevPosition != m_position)
		{
			calculateDirection();
			rotateSprite();
			setPreviousDirection();

			m_animatedSprite.setPosition(m_position);
			m_animatedSpriteBlood.setPosition(m_position.x, m_position.y + 5.f);

			m_moving = true;
			m_currentAnimation = AnimationManager::getAnimationByKey("knight-walk");
			m_animatedSprite.play(*m_currentAnimation);	

			m_prevPosition = m_position;
		}
		else
		{
			m_moving = false;
			auto& currentAnimation{ m_currentAnimation.value().get() };
			if (&currentAnimation == &AnimationManager::getAnimationByKey("knight-walk"))
			{
				m_animatedSprite.stop();
			}

			if (!m_animatedSprite.isPlaying())
			{
				m_currentAnimation = AnimationManager::getAnimationByKey("knight-idle");
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

		m_currentAnimation = AnimationManager::getAnimationByKey("knight-hurt");
		m_animatedSprite.play(*m_currentAnimation);
		m_animatedSpriteBlood.play();
	}

	void Player::verifyDeath(sf::Time elapsedTime)
	{
		if (m_health <= 0)
		{
			auto& currentAnimation{ m_currentAnimation.value().get() };
			if (m_active && (&currentAnimation != &AnimationManager::getAnimationByKey("knight-die")))
			{
				m_animatedSprite.pause();
				m_currentAnimation = AnimationManager::getAnimationByKey("knight-die");
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
		if (&currentAnimation == &AnimationManager::getAnimationByKey("knight-idle"))
		{
			m_animatedSprite.setFrameTime(sf::seconds(0.2f));
		}
		else if (&currentAnimation == &AnimationManager::getAnimationByKey("knight-attack") ||
			&currentAnimation == &AnimationManager::getAnimationByKey("knight-hurt"))
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

	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_animatedSprite);
	}
}
