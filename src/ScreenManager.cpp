#include "ScreenManager.h"
#include "Screen.h"
// ----------------------------------------------------------------------------
#include <stack>
// ----------------------------------------------------------------------------
namespace lpa
{
// ----------------------------------------------------------------------------
ScreenManager::ScreenManager(sf::RenderWindow* window)
	: m_window(window)
{
}

ScreenManager::~ScreenManager()
{
}

void ScreenManager::addScreen(Screen* screen)
{
	m_screens.push(screen);
}

void ScreenManager::removeScreen()
{
	delete m_screens.top();
	m_screens.pop();
}

Screen* ScreenManager::getScreen()
{
	if (m_screens.empty()) return nullptr;
	return m_screens.top();
}

void ScreenManager::changeScreen(Screen* screen)
{
	if (!m_screens.empty())
		removeScreen();
	addScreen(screen);
}

// ----------------------------------------------------------------------------
}
