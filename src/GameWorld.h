#pragma once
// -----------------------------------------
#include "pch.h"
#include "Arena.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Wave.h"
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
	class GameWorld : public Screen
	{
	public:
		GameWorld(ScreenManager* screenManager);

		virtual void handleInput();
		virtual void handleEvent(sf::Event event);
		virtual void update(sf::Time elapsedTime);
		void draw(sf::RenderTarget& target, sf::RenderStates states);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		static constexpr uint k_MaxWave{ 5 };
		using Waves = std::array<Wave, k_MaxWave>;

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

		uint				m_score;
		uint				m_highScore;
		bool				m_victory;
		Player				m_player;
		Arena				m_arena;
		uint				m_indexCurrentWave;
		Waves				m_waves;
		SpawnManager		m_spawnManager;
							
		sf::Music			m_orcCampMusic;
							
		sf::Font			m_orcHordeFont;
		Text				m_waveText;
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
		std::vector<Text*>	m_texts;
	};
}

