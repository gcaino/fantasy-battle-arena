#include "pch.h"
#include "AnimationManager.h"
// --------------------------------------------------------------------------
namespace lpa
{
	void AnimationManager::insert(std::string_view key)
	{
		// Find Animation Key, if exist not insert again in the container
		auto found = m_animations.find(key.data());
		if (found != m_animations.end()) return;

		// Insert New Animation in Container
		auto [it, result] = m_animations.emplace(std::make_pair(key.data(), Animation{}));

		std::string assertMsg{ std::string("Assert Error, Could not be possible Emplace Animation Key: ") + key.data() + '\n' };
		assert(result && assertMsg.c_str());
	}

	Animation& AnimationManager::getAnimationByKey(std::string_view key)
	{
		auto it = m_animations.find(key.data());

		std::string assertMsg{ std::string("Assert Error, Invalid Texture Key: ") + key.data() + '\n' };
		assert(it != m_animations.end() && assertMsg.c_str());

		return it->second;
	}
}
