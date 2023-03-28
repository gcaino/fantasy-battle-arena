#pragma once
// -----------------------------------------
#include "pch.h"
#include "entities\Arena.h"
#include "entities\Player.h"
#include "systems\EnemyManager.h"
#include "systems\SpawnManager.h"
#include "Screen.h"
#include "UI.h"
// -----------------------------------------
namespace lpa
{
	class ScreenManager;
	// -----------------------------------------
	class GameplayScreen : public Screen
	{
	public:
		GameplayScreen(ScreenManager& screenManager);

		void handleEvent(sf::Event event) override;
		void update(sf::Time elapsedTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		using Texts = std::vector<Ref<ui::Text>>;
		
		void pause();
		constexpr bool isPaused() const noexcept { return m_paused; }
		
		void setMousePointer();
		void updateMousePointer();

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

		EnemyManager		m_enemyManager;
		SpawnManager		m_spawnManager;

		Texts				m_texts;
		uint				m_score;
		uint				m_highScore;
		bool				m_victory;
		Player				m_player;
		Arena				m_arena;
		bool				m_paused;

		sf::Music			m_orcCampMusic;
		
		sf::Font			m_orcHordeFont;
		ui::Text			m_EnemyManagerText;
		ui::Text			m_scoreText;
		ui::Text			m_victoryText;
		ui::Text			m_defeatText;
		ui::Text			m_objectiveText;

		sf::Sprite			m_spriteMousePointer;
		sf::Sprite			m_orcsKilledBar;
		sf::Sprite			m_healthStatusBar;
		sf::Sprite			m_currentHealth;

		sf::Time			m_elapsedWaitTime;
		sf::Time			m_waitTime;
		sf::Time			m_victoryTime;
		sf::Time			m_elapsedVictoryTime;	
	};
}

