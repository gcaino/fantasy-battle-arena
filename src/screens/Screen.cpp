#include "pch.h"
#include "Screen.h"
// ----------------------------------------------------------------------------
#include "ScreenManager.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	Screen::Screen(ScreenManager& screenManager)
		: m_screenManager(screenManager)
	{
		auto& window { m_screenManager.get().getRenderWindow() };
		window.setMouseCursorVisible(true);
	}
}



