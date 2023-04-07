#pragma once
// ----------------------------------------------------------------------------
#include "pch.h"
// ----------------------------------------------------------------------------
namespace lpa::ui
{
	class Button
	{
	public:
		Button(sf::RenderWindow& window);

		void setCallback(std::function<void()> onClick);
		void setTexture(const sf::Texture& texture);
		void setPosition(sf::Vector2f position) { m_shape.setPosition(position); }
		
		constexpr void activate()   noexcept { m_active = true; }
		constexpr void deactivate() noexcept { m_active = false; }
		constexpr bool isActive() noexcept { return m_active; }
		
		bool isMouseOver() const;
		void click();
		void draw() const;

	private:
		Ref<sf::RenderWindow> m_window;
		sf::RectangleShape	  m_shape;
		sf::Font			  m_font;
		sf::Text			  m_text;
		std::function<void()> m_onClick;
		bool				  m_active;
	};

	struct Text
	{
		sf::Text text{};
		bool	 visible{};
	};
}