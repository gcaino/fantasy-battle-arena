#pragma once
// --------------------------------------------------------------------------------
#include "pch.h"
#include "ecs\Component.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	class KeyboardInputCmp : public Component
	{
	public:
		KeyboardInputCmp() = default;

		void bindKeyToAction(sf::Keyboard::Key key, std::string_view action);
		void bindActionsToCommands(std::string_view action, std::function<void(sf::Time elapsedTime)> command);
		void update(sf::Time elapsedTime);

	private:
		std::unordered_map<std::string_view, std::function<void(sf::Time elapsedTime)>> m_commands;
		std::unordered_map<sf::Keyboard::Key, std::string_view>		m_keys;
	};
}

