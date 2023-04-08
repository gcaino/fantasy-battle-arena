#pragma once
// --------------------------------------------------------------------------------
#include "pch.h"
#include "ecs\Component.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	class StatCmp : public Component
	{
	public:
		StatCmp() = default;

		float	health{};
		float	maxHealth{};
		uint	strength{};
		uint	evasion{};
		uint	level{};
		bool	alive{};
	};
}
