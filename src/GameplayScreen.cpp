#include "pch.h"
#include "GameplayScreen.h"
// -----------------------------------------
#include "AnimatedSprite.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "ScreenManager.h"
#include "TitleScreen.h"
#include "CreditsScreen.h"
// -----------------------------------------
namespace lpa
{
	bool compareAxisY(const AnimatedSprite& first, const AnimatedSprite& second)
	{
		return (first.getPosition().y < second.getPosition().y);
	}
	// -----------------------------------------
	GameplayScreen::GameplayScreen(ScreenManager& screenManager)
		: Screen(screenManager)
		, m_texts {}
		, m_indexCurrentWave {}
		, m_victory	{false}
		, m_spawnManager{ m_waves[0] }
		, m_score		{}
		, m_highScore	{}
		, m_waitTime	{ sf::seconds(10.f) }
		, m_victoryTime	{ sf::seconds(8.f) }
		, m_elapsedWaitTime		{ sf::Time::Zero }
		, m_elapsedVictoryTime	{ sf::Time::Zero }
	{
		initSounds();
		initTexts();

		m_healthStatusBarTexture.loadFromFile(Constants::textureHealthStatusBar);
		m_healthStatusBar.setTexture(m_healthStatusBarTexture);
		m_healthStatusBar.setPosition(sf::Vector2f(10.f, 15.f));
		m_currentHealthTexture.loadFromFile(Constants::textureCurrentHealth);
		m_currentHealth.setTexture(m_currentHealthTexture);
		m_currentHealth.setPosition(sf::Vector2f(76.f, 50.f));
		m_orcsKilledBarTexture.loadFromFile(Constants::textureOrcsKilledBar);
		m_orcsKilledBar.setTexture(m_orcsKilledBarTexture);
		m_orcsKilledBar.setPosition(sf::Vector2f(330.f, 15.f));
	}
	void GameplayScreen::initSounds()
	{
		m_orcCampMusic.openFromFile(Constants::orcCampMusic);
		m_orcCampMusic.setLoop(true);
		m_orcCampMusic.play();
	}

	void GameplayScreen::initTexts()
	{
		m_orcHordeFont.loadFromFile(Constants::ortHordeFont);
		m_waveText.text.setFont(m_orcHordeFont);
		m_waveText.text.setFillColor(sf::Color::Color(255, 175, 5));
		m_waveText.text.setCharacterSize(60);
		m_waveText.text.setStyle(sf::Text::Bold);
		m_waveText.text.setString("ORCS ARE COMING...");
		m_waveText.text.setPosition((Constants::k_WindowWidth * 0.5f) - (m_waveText.text.getGlobalBounds().width * 0.5f), Constants::k_WindowHeight * 0.2f);
		m_waveText.visible = true;

		m_objectiveText.text.setFont(m_orcHordeFont);
		m_objectiveText.text.setFillColor(sf::Color::Black);
		m_objectiveText.text.setCharacterSize(23);
		m_objectiveText.text.setString("[OBJECTIVE: Kill " + std::to_string(m_waves[m_indexCurrentWave].getMaxEnemies()) + " Orcs]");
		m_objectiveText.text.setPosition(sf::Vector2f(Constants::k_WindowWidth * 0.67f, 50.f));
		m_objectiveText.visible = true;

		m_scoreText.text.setFont(m_orcHordeFont);
		m_scoreText.text.setFillColor(sf::Color::Yellow);
		m_scoreText.text.setCharacterSize(23);
		m_scoreText.visible = true;

		m_victoryText.text.setFont(m_orcHordeFont);
		m_victoryText.text.setFillColor(sf::Color::Green);
		m_victoryText.text.setCharacterSize(120);
		m_victoryText.text.setStyle(sf::Text::Bold);
		m_victoryText.text.setString("VICTORY!!!");
		m_victoryText.text.setPosition((Constants::k_WindowWidth * 0.5f) - (m_victoryText.text.getGlobalBounds().width * 0.5f), Constants::k_WindowHeight * 0.2f);
		m_victoryText.visible = false;

		m_defeatText.text.setFont(m_orcHordeFont);
		m_defeatText.text.setFillColor(sf::Color::Red);
		m_defeatText.text.setCharacterSize(120);
		m_defeatText.text.setStyle(sf::Text::Bold);
		m_defeatText.text.setString("DEFEAT!!!");
		m_defeatText.text.setPosition((Constants::k_WindowWidth * 0.5f) - (m_defeatText.text.getGlobalBounds().width * 0.5f), Constants::k_WindowHeight * 0.2f);
		m_defeatText.visible = false;

		addTextsToDraw();
	}

	void GameplayScreen::addTextsToDraw()
	{
		m_texts.push_back(m_waveText);
		m_texts.push_back(m_scoreText);
		m_texts.push_back(m_victoryText);
		m_texts.push_back(m_defeatText);
		m_texts.push_back(m_objectiveText);
	}

	void GameplayScreen::updateTexts()
	{
		m_scoreText.text.setString("ORCS KILLED: " + std::to_string(m_player.getEnemiesKilled()));
		m_scoreText.text.setPosition(m_orcsKilledBar.getPosition().x + 78.f, m_orcsKilledBar.getPosition().y + 34.f);
	}

	void GameplayScreen::updateHealthBar(const Player& player)
	{
		m_currentHealth.setScale(static_cast<float>(player.getHealth() / player.getMaxHealth()), 1.f);
	}

	void GameplayScreen::showStartText(sf::Time elapsedTime)
	{
		m_elapsedWaitTime += elapsedTime;
		if (m_elapsedWaitTime > m_waitTime)
		{
			m_waveText.visible = false;
		}
	}

	void GameplayScreen::handleEvent(sf::Event event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				m_screenManager.get().changeScreen(std::make_unique<TitleScreen>(m_screenManager));
		}
	}

	void GameplayScreen::handleInput()
	{
		if (!m_player.isAlive())
			return;

		m_player.handlerInputs();
		m_player.handlerInputsAttack(m_waves[m_indexCurrentWave], m_screenManager.get().getRenderWindow());
	}
	void GameplayScreen::update(sf::Time elapsedTime)
	{
		if (m_player.isAlive())
		{
			m_player.update(elapsedTime);
			m_waves[m_indexCurrentWave].update(elapsedTime, m_player);

			collisionDetectionPlayerLimitsArena();
			collisionDetectionEnemiesLimitsArena(elapsedTime);
			collisionDetectionPlayerEnemies();
			collisionDetectionEnemiesPlayer();
			collisionDetectionEnemyEmemies(elapsedTime);
			checkAttackRangePlayer();
			checkAttackRangeEnemies();

			updateHealthBar(m_player);
			showStartText(elapsedTime);
			updateTexts();
			m_spawnManager.update(elapsedTime);

			checkVictoryCondition(elapsedTime);
		}
		else
		{
			checkLossCondition(elapsedTime);
		}
	}

	void GameplayScreen::checkVictoryCondition(sf::Time elapsedTime)
	{
		if (m_waves[m_indexCurrentWave].getMaxEnemies() == m_player.getEnemiesKilled())
		{
			m_victory = true;
			m_victoryText.visible = true;

			m_elapsedVictoryTime += elapsedTime;
			if (m_elapsedVictoryTime >= m_victoryTime)
			{
				m_screenManager.get().changeScreen(std::make_unique<CreditScreen>(m_screenManager));
			}
		}
	}

	void GameplayScreen::checkLossCondition(sf::Time elapsedTime)
	{
		if (m_player.getHealth() <= 0)
		{
			m_victory = false;
			m_defeatText.visible = true;

			m_elapsedVictoryTime += elapsedTime;
			if (m_elapsedVictoryTime >= m_victoryTime)
			{
				m_screenManager.get().changeScreen(std::make_unique<CreditScreen>(m_screenManager));
			}
		}
	}

	void GameplayScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}
	void GameplayScreen::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		target.draw(m_arena.getSprite(), sf::RenderStates::Default);
	
		std::list<AnimatedSprite> sprites;
		sprites.push_back(m_player.getAnimatedSprite());

		if (m_player.canDrawBlood())
		{
			sprites.push_back(m_player.getAnimatedSpriteBlood());
		}

		auto maxWaveEnemies { m_waves[m_indexCurrentWave].getMaxEnemies() };
		for (uint i { 0 }; i < maxWaveEnemies; i++)
		{
			const auto& enemy { m_waves[m_indexCurrentWave].getEnemyRefByIndex(i) };
			if (enemy.isAlive())
			{
				sprites.push_back(enemy.getAnimatedSprite());
				if (enemy.canDrawBlood())
				{
					sprites.push_back(enemy.getAnimatedSpriteBlood());
				}
			}
		}

		sprites.sort(compareAxisY);
	
		std::list<AnimatedSprite>::iterator it;
		for (it = sprites.begin(); it != sprites.end(); ++it)
		{
			target.draw(*it, sf::RenderStates::Default);
		}
		// HUD
		target.draw(m_healthStatusBar);
		target.draw(m_currentHealth);
		target.draw(m_orcsKilledBar);
		// Texts
		for (const auto& text : m_texts)
		{
			if (text.get().visible)
				target.draw(text.get().text);
		}
	}
	void GameplayScreen::collisionDetectionPlayerLimitsArena()
	{
		sf::Image imageArenaCollision = m_arena.getImageCollision();
	
		if (CollisionManager::pixelTest(m_player.getAnimatedSprite(), imageArenaCollision))
		{
			m_player.movePreviousPosition();
		}
	}
	void GameplayScreen::collisionDetectionEnemiesLimitsArena(sf::Time elapsedTime)
	{
		const sf::Image& imageArenaCollision { m_arena.getImageCollision() };
		auto maxWaveEnemies { m_waves[m_indexCurrentWave].getMaxEnemies() };
		for (uint i { 0 }; i < maxWaveEnemies; i++)
		{
			Enemy& enemy = m_waves.at(m_indexCurrentWave).getEnemyRefByIndex(i);
			if (enemy.isActive())
			{
				if (CollisionManager::pixelTest(enemy.getAnimatedSprite(), imageArenaCollision))
				{
					if (enemy.getPrevPosition().y > enemy.getPosition().y)
						enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + (enemy.getVelocity() * elapsedTime.asSeconds()));
					else
						enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y - (enemy.getVelocity() * elapsedTime.asSeconds()));
				}
			}
		}
	}
	void GameplayScreen::collisionDetectionPlayerEnemies()
	{
		auto maxWaveEnemies { m_waves[m_indexCurrentWave].getMaxEnemies() };
		for (uint i { 0 }; i < maxWaveEnemies; i++)
		{
			Enemy* pEnemy = &m_waves[m_indexCurrentWave].getEnemyRefByIndex(i);
			if (pEnemy->isActive())
			{
				if (CollisionManager::boundingBoxTest(m_player.getAnimatedSprite(), pEnemy->getAnimatedSprite(), 0.5f))
				{
					m_player.movePreviousPosition();
				}
			}
		}
	}

	void GameplayScreen::collisionDetectionEnemiesPlayer()
	{
		auto maxWaveEnemies { m_waves[m_indexCurrentWave].getMaxEnemies() } ;
		for (uint i { 0 }; i < maxWaveEnemies; i++)
		{
			Enemy* pEnemy = &m_waves[m_indexCurrentWave].getEnemyRefByIndex(i);
			if (pEnemy->isActive())
			{
				if (CollisionManager::boundingBoxTest(pEnemy->getAnimatedSprite(), m_player.getAnimatedSprite(), 0.5f))
				{
					pEnemy->movePreviousPosition();
				}
			}
		}
	}

	void GameplayScreen::checkAttackRangeEnemies()
	{
		auto maxWaveEnemies { m_waves[m_indexCurrentWave].getMaxEnemies() };
		for (uint i { 0 }; i < maxWaveEnemies; i++)
		{
			Enemy* pEnemy = &m_waves[m_indexCurrentWave].getEnemyRefByIndex(i);
			if (pEnemy->isActive())
			{
				if (CollisionManager::boundingBoxRangeAttack(pEnemy->getAnimatedSprite(), m_player.getAnimatedSprite(), 0.3f))
				{
					pEnemy->attack(m_player);
				}
			}
		}
	}

	void GameplayScreen::checkAttackRangePlayer()
	{
		auto maxWaveEnemies { m_waves[m_indexCurrentWave].getMaxEnemies() };
		for (uint i = 0; i < maxWaveEnemies; i++)
		{
			auto& enemy = m_waves[m_indexCurrentWave].getEnemyRefByIndex(i);
			if (enemy.isActive())
			{
				if (CollisionManager::boundingBoxRangeAttack(m_player.getAnimatedSprite(), enemy.getAnimatedSprite(), 0.3f))
				{
					m_player.addAttackableEnemy(enemy);
				}
				else
				{
					m_player.removeAttackableEnemy(enemy);
				}
			}
		}
	}

	void GameplayScreen::collisionDetectionEnemyEmemies(sf::Time elapsedTime)
	{
		auto maxWaveEnemies { m_waves[m_indexCurrentWave].getMaxEnemies() } ;
		for (uint i { 0 }; i < maxWaveEnemies - 1; i++)
		{
			Enemy* enemy = &m_waves[m_indexCurrentWave].getEnemyRefByIndex(i);
			if (enemy->isActive())
			{
				for (uint j = 0; j < maxWaveEnemies; j++)
				{
					Enemy* enemy2 = &m_waves[m_indexCurrentWave].getEnemyRefByIndex(j);
					if (enemy2->isActive() && (enemy != enemy2))
					{
						if (CollisionManager::boundingBoxTest(enemy->getAnimatedSprite(), enemy2->getAnimatedSprite(), 0.7f))
						{
							enemy->movePreviousPosition();
							if ((enemy->getPosition().y + (enemy->getVelocity() * elapsedTime.asSeconds())) < Constants::k_WindowHeight - 30.f)
							{
								enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y + (enemy->getVelocity() * elapsedTime.asSeconds()));
							}
							return;
						}
					}
				}
			}
		}
	}
}
