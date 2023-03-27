#pragma once
// -----------------------------------------
#include "pch.h"
#include "entities\Arena.h"
#include "entities\Player.h"
#include "systems\EnemyManager.h"
#include "systems\SpawnManager.h"
#include "Screen.h"
// -----------------------------------------
namespace lpa
{
	struct Text
	{
		sf::Text text	{};
		bool	 visible{};
	};
	class ScreenManager;
	// -----------------------------------------
	class GameplayScreen : public Screen
	{
	public:
		GameplayScreen(ScreenManager& screenManager);

		virtual void handleInput();
		virtual void handleEvent(sf::Event event);
		virtual void update(sf::Time elapsedTime);
		void draw(sf::RenderTarget& target, sf::RenderStates states);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		using Texts = std::vector<Ref<Text>>;
		
		void pause();
		constexpr bool isPaused() const noexcept { return m_paused; }
		
		void initTexts();
		void addTextsToDraw();
		void updateTexts();
		void showStartText(sf::Time elapsedTime);
		void updateHealthBar(const Player& player);
		void initSounds();
		void checkVictoryCondition(sf::Time elapsedTime);
		void checkLossCondition(sf::Time elapsedTime);

		void collisionDetectionPlayerLimitsArena();
		void collisionDetectionEnemiesLimitsArena(sf::Time elapsedTime);
		void collisionDetectionPlayerEnemies();
		void collisionDetectionEnemiesPlayer();
		void collisionDetectionEnemyEmemies(sf::Time elapsedTime);
		void checkAttackRangeEnemies();
		void checkAttackRangePlayer();

		Texts				m_texts;
		uint				m_score;
		uint				m_highScore;
		bool				m_victory;
		Player				m_player;
		Arena				m_arena;
		EnemyManager		m_enemyManager;
		SpawnManager		m_spawnManager;
		bool				m_paused;

		sf::Music			m_orcCampMusic;
							
		sf::Font			m_orcHordeFont;
		Text				m_EnemyManagerText;
		Text				m_scoreText;
		Text				m_victoryText;
		Text				m_defeatText;
		Text				m_objectiveText;
		sf::Texture			m_healthStatusBarTexture;
		sf::Texture			m_currentHealthTexture;
		sf::Texture			m_orcsKilledBarTexture;
		sf::Sprite			m_orcsKilledBar;
		sf::Sprite			m_healthStatusBar;
		sf::Sprite			m_currentHealth;
		sf::Time			m_elapsedWaitTime;
		sf::Time			m_waitTime;
		sf::Time			m_victoryTime;
		sf::Time			m_elapsedVictoryTime;	
	};
}

