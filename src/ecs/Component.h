#pragma once
// ---------------------------------------------------------------------------
#include "pch.h"
// ---------------------------------------------------------------------------
namespace lpa
{
	class Entity;
	class MovementCmp;
	class KeyboardInputCmp;
	class SpriteCmp;
	class StatCmp;
	// -----------------------------------------------------------------------
	class Component
	{
	public:
		// TODO: cada vez que se agrega un componente hay que recompilar, se puede incoporar por .json
		enum class Type
		{
			None,
			Sprite,
			Movement,
			KeyboardInput,
			Stat
		};

		Component() = default;
		virtual ~Component() = default;

		constexpr void activate()		noexcept { m_active = true; }
		constexpr void deactivate()		noexcept { m_active = false; }
		constexpr bool isActive() const	noexcept { return m_active; }

		template<typename CmpType>
		static Component::Type getComponentType()
		{
			Component::Type cmpType{ Component::Type::None };
			if constexpr (std::is_same<CmpType, MovementCmp>::value)
			{
				cmpType = Component::Type::Movement;
			}
			else if constexpr (std::is_same<CmpType, SpriteCmp>::value)
			{
				cmpType = Component::Type::Sprite;
			}
			else if constexpr (std::is_same<CmpType, KeyboardInputCmp>::value)
			{
				cmpType = Component::Type::KeyboardInput;
			}
			else if constexpr (std::is_same<CmpType, StatCmp>::value)
			{
				cmpType = Component::Type::Stat;
			}
			return cmpType;
		}

		friend Entity;

	private:
		Type type		{ Type::None };
		bool m_active	{ true };
	};
}
