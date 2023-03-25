#include "GameWorld.h"
// -----------------------------------------
#include "AnimatedSprite.h"
#include "Constants.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "ScreenManager.h"
#include "TitleScreen.h"
#include "CreditsScreen.h"
#include <iostream>
#include <list>
#include <iterator>
#include <cmath>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
bool compareAxisY(const AnimatedSprite& first, const AnimatedSprite& second)
{
	return (first.getPosition().y < second.getPosition().y);
}
// -----------------------------------------
GameWorld::GameWorld(ScreenManager* screenManager)
	: Screen(screenManager)
	, _indexCurrentWave(0)
	, _victory(false)
	, _spawnManager(&_waves[0])
	, _score(0)
	, _highScore(0)
	, _waitTime(sf::seconds(10.f))
	, _victoryTime(sf::seconds(8.f))
	, _elapsedWaitTime(sf::Time::Zero)
	, _elapsedVictoryTime(sf::Time::Zero)
{
	initSounds();
	initTexts();

	_healthStatusBarTexture.loadFromFile(Constants::textureHealthStatusBar);
	_healthStatusBar.setTexture(_healthStatusBarTexture);
	_healthStatusBar.setPosition(sf::Vector2f(10.f, 15.f));
	_currentHealthTexture.loadFromFile(Constants::textureCurrentHealth);
	_currentHealth.setTexture(_currentHealthTexture);
	_currentHealth.setPosition(sf::Vector2f(76.f, 50.f));
	_orcsKilledBarTexture.loadFromFile(Constants::textureOrcsKilledBar);
	_orcsKilledBar.setTexture(_orcsKilledBarTexture);
	_orcsKilledBar.setPosition(sf::Vector2f(330.f, 15.f));
}
GameWorld::~GameWorld()
{
}

void GameWorld::initSounds()
{
	_orcCampMusic.openFromFile(Constants::orcCampMusic);
	_orcCampMusic.setLoop(true);
	_orcCampMusic.play();
}

void GameWorld::initTexts()
{
	_orcHordeFont.loadFromFile(Constants::ortHordeFont);
	_waveText.text.setFont(_orcHordeFont);
	_waveText.text.setFillColor(sf::Color::Color(255, 175, 5));
	_waveText.text.setCharacterSize(60);
	_waveText.text.setStyle(sf::Text::Bold);
	_waveText.text.setString("ORCS ARE COMING...");
	_waveText.text.setPosition(Constants::WINDOW_WIDTH_MAX / 2 - _waveText.text.getGlobalBounds().width / 2, Constants::WINDOW_HEIGHT_MAX * 0.2f);
	_waveText.visible = true;

	_objectiveText.text.setFont(_orcHordeFont);
	_objectiveText.text.setFillColor(sf::Color::Black);
	_objectiveText.text.setCharacterSize(23);
	//_objectiveText.text.setStyle(sf::Text::Bold);
	_objectiveText.text.setString("[OBJECTIVE: Kill " + std::to_string(_waves->getMaxEnemies()) + " Orcs]");
	_objectiveText.text.setPosition(sf::Vector2f(Constants::WINDOW_WIDTH_MAX * 0.67f, 50.f));
	_objectiveText.visible = true;

	_scoreText.text.setFont(_orcHordeFont);
	_scoreText.text.setFillColor(sf::Color::Yellow);
	_scoreText.text.setCharacterSize(23);
	_scoreText.visible = true;

	_victoryText.text.setFont(_orcHordeFont);
	_victoryText.text.setFillColor(sf::Color::Green);
	_victoryText.text.setCharacterSize(120);
	_victoryText.text.setStyle(sf::Text::Bold);
	_victoryText.text.setString("VICTORY!!!");
	_victoryText.text.setPosition(Constants::WINDOW_WIDTH_MAX / 2 - _victoryText.text.getGlobalBounds().width / 2, Constants::WINDOW_HEIGHT_MAX * 0.2f);
	_victoryText.visible = false;

	_defeatText.text.setFont(_orcHordeFont);
	_defeatText.text.setFillColor(sf::Color::Red);
	_defeatText.text.setCharacterSize(120);
	_defeatText.text.setStyle(sf::Text::Bold);
	_defeatText.text.setString("DEFEAT!!!");
	_defeatText.text.setPosition(Constants::WINDOW_WIDTH_MAX / 2 - _defeatText.text.getGlobalBounds().width / 2, Constants::WINDOW_HEIGHT_MAX * 0.2f);
	_defeatText.visible = false;

	addTextsToDraw();
}

void GameWorld::addTextsToDraw()
{
	_texts.push_back(&_waveText);
	_texts.push_back(&_scoreText);
	_texts.push_back(&_victoryText);
	_texts.push_back(&_defeatText);
	_texts.push_back(&_objectiveText);
}

void GameWorld::updateTexts()
{
	_scoreText.text.setString("ORCS KILLED: " + std::to_string(_player.getEnemiesKilled()));
	_scoreText.text.setPosition(_orcsKilledBar.getPosition().x + 78.f, _orcsKilledBar.getPosition().y + 34.f);
}

void GameWorld::updateHealthBar(const Player& player)
{
	_currentHealth.setScale(static_cast<float>(player.getHealth() / player.getMaxHealth()), 1.f);
}

void GameWorld::showStartText(sf::Time elapsedTime)
{
	_elapsedWaitTime += elapsedTime;
	if (_elapsedWaitTime > _waitTime)
	{
		_waveText.visible = false;
	}
}

void GameWorld::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			m_screenManager->changeScreen(new TitleScreen(m_screenManager));
	}
}

void GameWorld::handleInput()
{
	if (!_player.isAlive())
		return;

	_player.handlerInputs();
	_player.handlerInputsAttack(_waves, m_screenManager->getRenderWindow());
}
void GameWorld::update(sf::Time elapsedTime)
{
	if (_player.isAlive())
	{
		_player.update(elapsedTime);
		_waves[_indexCurrentWave].update(elapsedTime, &_player);

		collisionDetectionPlayerLimitsArena();
		collisionDetectionEnemiesLimitsArena(elapsedTime);
		collisionDetectionPlayerEnemies();
		collisionDetectionEnemiesPlayer();
		collisionDetectionEnemyEmemies(elapsedTime);
		checkAttackRangePlayer();
		checkAttackRangeEnemies();

		updateHealthBar(_player);
		showStartText(elapsedTime);
		updateTexts();
		_spawnManager.update(elapsedTime);

		checkVictoryCondition(elapsedTime);
	}
	else
	{
		checkLossCondition(elapsedTime);
	}
}

void GameWorld::checkVictoryCondition(sf::Time elapsedTime)
{
	if (_waves->getMaxEnemies() == _player.getEnemiesKilled())
	{
		_victory = true;
		_victoryText.visible = true;

		_elapsedVictoryTime += elapsedTime;
		if (_elapsedVictoryTime >= _victoryTime)
		{
			m_screenManager->changeScreen(new CreditScreen(m_screenManager));
		}
	}
}

void GameWorld::checkLossCondition(sf::Time elapsedTime)
{
	if (_player.getHealth() <= 0)
	{
		_victory = false;
		_defeatText.visible = true;

		_elapsedVictoryTime += elapsedTime;
		if (_elapsedVictoryTime >= _victoryTime)
		{
			m_screenManager->changeScreen(new CreditScreen(m_screenManager));
		}
	}
}

void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(_arena.getSprite(), sf::RenderStates::Default);
	
	std::list<AnimatedSprite> sprites;
	sprites.push_back(_player.getAnimatedSprite());

	if (_player.canDrawBlood())
	{
		sprites.push_back(_player.getAnimatedSpriteBlood());
	}

	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	Enemy* pEnemy = nullptr;
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		pEnemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (pEnemy->isAlive())
		{
			sprites.push_back(pEnemy->getAnimatedSprite());
			if (pEnemy->canDrawBlood())
			{
				sprites.push_back(pEnemy->getAnimatedSpriteBlood());
			}
		}
	}

	sprites.sort(compareAxisY);
	
	std::list<AnimatedSprite>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); ++it)
	{
		// Escalar Texturas (Comentado, no me termina de gustar el gameplay que genera y el pixelado)
		/*if (it != sprites.begin())
		{
			float targetSizeY	= static_cast<float>(target.getSize().y / 2);
			float spritePosY	= (*it).getPosition().y;
			float diffAbs		= abs(targetSizeY - spritePosY);
			float diffRel		= diffAbs / targetSizeY;

			if (diffRel > 0.25f)	diffRel = 0.25f;

			if (spritePosY < targetSizeY)
			{
				(*it).setScale(1 - diffRel, 1 - diffRel);
			}
			else if (spritePosY > targetSizeY)
			{
				(*it).setScale(1 + diffRel, 1 + diffRel);
			}
			else
			{
				(*it).setScale(1, 1);
			}
		}*/
		// Dibujar
		target.draw(*it, sf::RenderStates::Default);
	}
	// HUD
	target.draw(_healthStatusBar);
	target.draw(_currentHealth);
	target.draw(_orcsKilledBar);
	// Texts
	for (size_t i = 0; i < _texts.size(); i++)
	{
		if (_texts.at(i)->visible)
			target.draw(_texts.at(i)->text);
	}
}
void GameWorld::collisionDetectionPlayerLimitsArena()
{
	sf::Image imageArenaCollision = _arena.getImageCollision();
	
	if (CollisionManager::pixelTest(_player.getAnimatedSprite(), imageArenaCollision))
	{
		//std::cout << "Player Pixel Collision" << std::endl;
		_player.movePreviousPosition();
	}
}
void GameWorld::collisionDetectionEnemiesLimitsArena(sf::Time elapsedTime)
{
	sf::Image imageArenaCollision = _arena.getImageCollision();
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* enemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (enemy->isActive())
		{
			if (CollisionManager::pixelTest(enemy->getAnimatedSprite(), imageArenaCollision))
			{
				//enemy->movePreviousPosition();
				if (enemy->getPrevPosition().y > enemy->getPosition().y)
					enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y + (enemy->getVelocity() * elapsedTime.asSeconds()));
				else
					enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y - (enemy->getVelocity() * elapsedTime.asSeconds()));
			}
		}
	}
}
void GameWorld::collisionDetectionPlayerEnemies()
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* pEnemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (pEnemy->isActive())
		{
			if (CollisionManager::boundingBoxTest(_player.getAnimatedSprite(), pEnemy->getAnimatedSprite(), 0.5f))
			{
				std::cout << "Collision" << std::endl;
				_player.movePreviousPosition();
			}
		}
	}
}

void GameWorld::collisionDetectionEnemiesPlayer()
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* pEnemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (pEnemy->isActive())
		{
			if (CollisionManager::boundingBoxTest(pEnemy->getAnimatedSprite(), _player.getAnimatedSprite(), 0.5f))
			{
				pEnemy->movePreviousPosition();
			}
		}
	}
}

void GameWorld::checkAttackRangeEnemies()
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* pEnemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (pEnemy->isActive())
		{
			if (CollisionManager::boundingBoxRangeAttack(pEnemy->getAnimatedSprite(), _player.getAnimatedSprite(), 0.3f))
			{
				pEnemy->addAttackablePlayer(&_player);
			}
			else
			{
				pEnemy->removeAttackablePlayer(&_player);
			}
		}
	}
}

void GameWorld::checkAttackRangePlayer()
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* pEnemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (pEnemy->isActive())
		{
			if (CollisionManager::boundingBoxRangeAttack(_player.getAnimatedSprite(), pEnemy->getAnimatedSprite(), 0.3f))
			{
				_player.addAttackableEnemy(pEnemy);
			}
			else
			{
				_player.removeAttackableEnemy(pEnemy);
			}
		}
	}
}

void GameWorld::collisionDetectionEnemyEmemies(sf::Time elapsedTime)
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies - 1; i++)
	{
		Enemy* enemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (enemy->isActive())
		{
			for (uint j = 0; j < maxWaveEnemies; j++)
			{
				Enemy* enemy2 = &_waves[_indexCurrentWave].getEnemyRefByIndex(j);
				if (enemy2->isActive() && (enemy != enemy2))
				{
					if (CollisionManager::boundingBoxTest(enemy->getAnimatedSprite(), enemy2->getAnimatedSprite(), 0.7f))
					{
						enemy->movePreviousPosition();
						if ((enemy->getPosition().y + (enemy->getVelocity() * elapsedTime.asSeconds())) < Constants::WINDOW_HEIGHT_MAX - 30.f)
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

// -----------------------------------------
}
