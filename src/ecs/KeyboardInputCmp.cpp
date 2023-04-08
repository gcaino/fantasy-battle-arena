#include "pch.h"
#include "KeyboardInputCmp.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	void KeyboardInputCmp::bindKeyToAction(sf::Keyboard::Key key, std::string_view action)
	{
		auto [it, result] = m_keys.try_emplace(key, action);
		
		if (!result)
			throw std::runtime_error("Could not be possible emplace Key in container.");
	}

	void KeyboardInputCmp::bindActionsToCommands(std::string_view action, std::function<void(sf::Time elapsedTime)> command)
	{
		auto [it, result] = m_commands.try_emplace(action, command);

		if (!result)
			throw std::runtime_error("Could not be possible emplace Action in container.");
	}

	void KeyboardInputCmp::update(sf::Time elapsedTime)
	{
		for (auto& [key, action] : m_keys) {
			if (sf::Keyboard::isKeyPressed(key)) {
				m_commands.at(action)(elapsedTime);
				break;
			}
		}
	}
}
