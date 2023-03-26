#pragma once
// ----------------------------------------------------------------------------
#include "pch.h"
#include "Screen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	struct Button
	{
		bool		  visible {};
		sf::FloatRect rect	  {};
		sf::Texture	  texture {};
		sf::Sprite	  sprite  {};
	};
	// ----------------------------------------------------------------------------
	class TitleScreen : public Screen
	{
	public:
		TitleScreen(ScreenManager* screenManager);

		virtual void handleEvent(sf::Event event);
		virtual void update(sf::Time elapsedTime);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

	private:
		static constexpr uint k_MaxButtons { 2 };

		Button			m_buttons[k_MaxButtons];
		sf::SoundBuffer	m_soundBufferButtonClick;
		sf::Sound		m_soundButtonClick;
	};
}



