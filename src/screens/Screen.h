#pragma once
// ----------------------------------------------------------------------------
#include "pch.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	class ScreenManager;
	// ------------------------------------------------------------------------
	class Screen : public sf::Drawable
	{
	public:
		Screen(ScreenManager& screenManager);
		virtual ~Screen() = default;

		Screen(const Screen&)					= delete;
		Screen& operator=(const Screen&)		= delete;
		Screen(Screen&&)			noexcept	= delete;
		Screen& operator=(Screen&&) noexcept	= delete;

		virtual void handleEvent(sf::Event event) = 0;
		virtual void update(sf::Time elapsedTime) {};
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	protected:
		Ref<ScreenManager>	m_screenManager;
	};
}

