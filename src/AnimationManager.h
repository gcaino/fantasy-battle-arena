#pragma once
#include "pch.h"
#include "Animation.h"
// --------------------------------------------------------------------------
namespace lpa
{
	class AnimationManager final
	{
	public:
		AnimationManager() = delete;

		static void insert(std::string_view key);
		static Animation& getAnimationByKey(std::string_view key);

	private:
		inline static std::unordered_map<std::string, Animation> m_animations;
	};
}
