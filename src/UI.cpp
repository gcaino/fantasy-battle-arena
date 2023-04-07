#include "pch.h"
#include "UI.h"

namespace lpa::ui
{
	Button::Button(sf::RenderWindow& window)
		: m_window  {window}
		, m_shape   {}
		, m_font    {}
		, m_text    {}
		, m_onClick {nullptr}
		, m_active  {false}
	{
	}

	void Button::setCallback(std::function<void()> onClick)
	{
		m_onClick = onClick;
	}

	void Button::setTexture(const sf::Texture& texture)
	{
		m_shape.setTexture(&texture);
		
		sf::Vector2f size { static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y) };
		m_shape.setSize(size);
	}

	bool Button::isMouseOver() const
	{
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(m_window));
		return m_shape.getGlobalBounds().contains(mousePosition);
	}

	void Button::click()
	{
		if (m_onClick != nullptr)
			m_onClick();
	}

	void Button::draw() const
	{
		if (m_active)
			m_window.get().draw(m_shape);
	}
}