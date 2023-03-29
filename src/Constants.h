#pragma once
// --------------------------------------------------------------------------------
#include "pch.h"
// --------------------------------------------------------------------------------
namespace Constants
{
	static constexpr unsigned int	  k_WindowWidth  { 1024 };
	static constexpr unsigned int	  k_WindowHeight { 768 };
	static constexpr std::string_view k_WindowTitle  { "Fantasy Clicker" };

	const std::string orcCampMusic			= "assets/sounds/orc-camp.ogg";
	const std::string clickButtonSound		= "assets/sounds/click-wooden.wav";
	const std::string battleAxeSwingSound	= "assets/sounds/battle-axe-swing.ogg";
	const std::string orcAttackSound		= "assets/sounds/orc-attack.ogg";
	const std::string orcDieSound			= "assets/sounds/orc-die.ogg";

	const std::string ortHordeFont			= "assets/fonts/OrcHordeBB_Reg.ttf";
	const std::string creditScreenFont		= "assets/fonts/ARLRDBD.TTF";
}


