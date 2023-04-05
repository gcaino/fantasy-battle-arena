#pragma once
// -----------------------------------------
#include "pch.h"
#include "AnimatedSprite.h"
#include "Animation.h"
#include "cmp\MovementCmp.h"
#include "cmp\SpriteCmp.h"
// -----------------------------------------
namespace lpa
{
	class Character
	{
	public:
		Character();
		virtual ~Character() = default;

		virtual void initialize() = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		AnimatedSprite	getAnimatedSprite() const { return m_animatedSprite; }
		AnimatedSprite	getAnimatedSpriteBlood() const { return m_animatedSpriteBlood; }

		bool			isAlive() const { return m_alive; }
		void			setAlive(bool alive) { m_alive = alive; }
		
		bool			isActive() const { return m_active; }
		void			setActive(bool active) { m_active = active; }
		
		float			getHealth() const { return m_health; }
		float			getMaxHealth() const { return m_maxHealth; }

	protected:
		std::optional<Ref<Animation>>	m_currentAnimation;

		AnimatedSprite	m_animatedSprite;

		AnimatedSprite	m_animatedSpriteBlood;
		Animation		m_bloodAnimation;

		sf::Time		m_deadTime;
		sf::Time		m_elapsedDeadTime;

		float			m_health;
		float			m_maxHealth;
		uint			m_strength;
		uint			m_evasion;
		uint			m_level;
		bool			m_alive;
		bool			m_active;
	};
}
