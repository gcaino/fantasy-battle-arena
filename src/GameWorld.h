#ifndef GAMEWORLD_H
#define GAMEWORLD_H
// -----------------------------------------
#include "Arena.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Wave.h"
#include "Screen.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
const uint WAVE_MAX = 5;

struct Text
{
	sf::Text	text;
	bool		visible;
};
class ScreenManager;
// -----------------------------------------
class GameWorld : public Screen
{
private:
	uint					_score;
	uint					_highScore;
	bool					_victory;
	Player					_player;
	Arena					_arena;
	uint					_indexCurrentWave;
	Wave					_waves[WAVE_MAX];
	SpawnManager			_spawnManager;

	sf::Music				_orcCampMusic;

	sf::Font				_orcHordeFont;
	Text					_waveText;
	Text					_scoreText;
	Text					_victoryText;
	Text					_defeatText;
	Text					_objectiveText;
	sf::Texture				_healthStatusBarTexture;
	sf::Texture				_currentHealthTexture;
	sf::Texture				_orcsKilledBarTexture;
	sf::Sprite				_orcsKilledBar;
	sf::Sprite				_healthStatusBar;
	sf::Sprite				_currentHealth;
	sf::Time				_elapsedWaitTime;
	sf::Time				_waitTime;
	sf::Time				_victoryTime;
	sf::Time				_elapsedVictoryTime;
	std::vector<Text*>		_texts;

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

public:
	GameWorld(ScreenManager* screenManager);
	~GameWorld();

	virtual void handleInput();
	virtual void handleEvent(sf::Event event);
	virtual void update(sf::Time elapsedTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
// -----------------------------------------
}
// -----------------------------------------
#endif // GAMEWORLD_H
