#include "pch.h"
#include "ScreenManager.h"
// ----------------------------------------------------------------------------
#include "Screen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	ScreenManager::ScreenManager(sf::RenderWindow& window)
		: m_screens{}
		, m_window { window }
	{
	}
	void ScreenManager::addScreen(UPtr<Screen> screen)
	{
		m_screens.emplace(std::move(screen));
	}
	void ScreenManager::removeScreen()
	{
		m_screens.pop();
	}
	const Screen& ScreenManager::getScreen() const
	{
		assert(!m_screens.empty() && "Screen container is empty");

		return *m_screens.top().get();
	}
	Screen& ScreenManager::getScreen()
	{
		return const_cast<Screen&>(std::as_const(*this).getScreen());
	}
	void ScreenManager::changeScreen(UPtr<Screen> screen)
	{
		if (!m_screens.empty())
			removeScreen();
		addScreen(std::move(screen));
	}
}
