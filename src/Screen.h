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

		virtual void handleInput();
		virtual void handleEvent(sf::Event event) = 0;
		virtual void update(sf::Time elapsedTime) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

	protected:
		sf::Texture			m_texture;
		sf::Sprite			m_sprite;
		Ref<ScreenManager>	m_screenManager;

	};
}

