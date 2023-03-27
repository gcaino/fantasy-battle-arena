#pragma once
// ----------------------------------------------------------------------------
#include "pch.h"
#include "Screen.h"
#include "UI.h"
// ----------------------------------------------------------------------------
namespace lpa
{
	class TitleScreen : public Screen
	{
	public:
		TitleScreen(ScreenManager& screenManager);

		void handleEvent(sf::Event event) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		static constexpr uint k_MaxButtons { 2 };

		sf::Texture		m_backgroundTexture;
		sf::Sprite		m_backgroundSprite;
		ui::Button		m_buttons[k_MaxButtons];
		sf::SoundBuffer	m_soundBufferButtonClick;
		sf::Sound		m_soundButtonClick;
	};
}



