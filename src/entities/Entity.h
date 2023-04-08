#pragma once
// -----------------------------------------
#include "pch.h"
// -----------------------------------------
namespace lpa
{
	class Entity
	{
	public:
		Entity() = default;

		constexpr void activate()		noexcept { m_active = true; }
		constexpr void deactivate()		noexcept { m_active = false; }
		constexpr bool isActive() const	noexcept { return m_active; }

	private:
		bool m_active { false };
	};
}
