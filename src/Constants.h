#ifndef CONSTANTS_H
#define CONSTANTS_H
// -----------------------------------------
#include <string>
#include <SFML\System.hpp>
// -----------------------------------------
namespace Constants
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;

const uint WINDOW_WIDTH_MAX = 1024;
const uint WINDOW_HEIGHT_MAX = 768;

const std::string	texturesPath = "assets/textures/";
const std::string	texturesPathMousePointerSword = "assets/textures/mouse-pointer-32.png";
const std::string	texturesPathMousePointerAxe = "assets/textures/mouse-pointer-axe-32.png";
const std::string	texturePathArena = "assets/textures/arena-01-1024.png";
const std::string	texturePathArenaCollision = "assets/textures/arena-01-collision-1024.png";
const std::string	texturePathOrc = "assets/textures/orc-01.png";
const std::string	texturePathRedBlood = "assets/textures/spritesheets/effects/red-blood.png";
const std::string	texturePathGreenBlood = "assets/textures/spritesheets/effects/green-blood.png";

const std::string texturePlayerIdleAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-idle-b.png";
const std::string texturePlayerWalkAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-walk-b.png";
const std::string texturePlayerAttackAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-attack-b.png";
const std::string texturePlayerHurtAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-hurt-b.png";
const std::string texturePlayerDieAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-die-b.png";

const std::string textureOrcIdleAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-idle-b.png";
const std::string textureOrcWalkAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-walk-b.png";
const std::string textureOrcAttackAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-attack-b.png";
const std::string textureOrcHurtAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-hurt-b.png";
const std::string textureOrcDieAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-die-b.png";

const std::string textureMenuScreen = "assets/textures/menu-screen.jpg";

const std::string orcCampMusic = "assets/sounds/orc-camp.ogg";
const std::string clickButtonSound = "assets/sounds/click-wooden.wav";
const std::string battleAxeSwingSound = "assets/sounds/battle-axe-swing.ogg";
const std::string orcAttackSound = "assets/sounds/orc-attack.ogg";
const std::string orcDieSound = "assets/sounds/orc-die.ogg";

const std::string ortHordeFont = "assets/fonts/OrcHordeBB_Reg.ttf";
const std::string creditScreenFont = "assets/fonts/ARLRDBD.TTF";

const std::string pathTitleScreenImage = "assets/textures/menu-screen.jpg";
const std::string pathCreditsScreenImage = "assets/textures/credits-screen-1024.png";

const std::string textureCreditsButton = "assets/textures/button-credits-hover.png";
const std::string texturePlayButton = "assets/textures/button-play-hover.png";
const std::string textureHealthStatusBar = "assets/textures/healthStatusBar-1024.png";
const std::string textureCurrentHealth = "assets/textures/currentHelath-1024.png";
const std::string textureOrcsKilledBar = "assets/textures/orcs-killed-bar-1024.png";

// -----------------------------------------
}
// -----------------------------------------
#endif // !CONSTANTS_H

