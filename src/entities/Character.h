#pragma once
// -----------------------------------------
#include "pch.h"
#include "AnimatedSprite.h"
#include "Animation.h"
#include "GameObject.h"
// -----------------------------------------
namespace lpa
{
	class Character : public GameObject
	{
	public:
		enum class DirectionAxis
		{
			Left, Right, Up, Down
		};
		struct Direction
		{
			DirectionAxis	axisX;
			DirectionAxis   axisY;
		};

		Character();
		virtual ~Character() = default;

		AnimatedSprite	getAnimatedSprite() const { return m_animatedSprite; }
		AnimatedSprite	getAnimatedSpriteBlood() const { return m_animatedSpriteBlood; }
		bool			canDrawBlood() const { return m_drawBlood; }
		void			setDrawBlood(bool drawBlood) { m_drawBlood = drawBlood; }
		sf::Vector2f	getPosition() const { return m_position; }
		void			setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
		void			setPosition(float x, float y) { m_position.x = x; m_position.y = y; }
		Direction		getDirection() const { return m_direction; }
		void			setDirection(Direction newDirection) { m_direction = newDirection; }
		sf::Vector2f	getPrevPosition() const { return m_prevPosition; }
		void			setPrevPosition(sf::Vector2f prevPosition) { m_position = prevPosition; }
		bool			isAlive() const { return m_alive; }
		void			setAlive(bool alive) { m_alive = alive; }
		bool			isActive() const { return m_active; }
		void			setActive(bool active) { m_active = active; }
		float			getHealth() const { return m_health; }
		float			getMaxHealth() const { return m_maxHealth; }
		float			getVelocity() const { return m_velocity; }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		void calculateDirection();
		void rotateSprite();

	protected:
		std::optional<Ref<Animation>>	m_currentAnimation;

		AnimatedSprite	m_animatedSprite;

		Animation		m_walkingAnimation;
		Animation		m_attackAnimation;
		Animation		m_hurtAnimation;
		Animation		m_dieAnimation;
		Animation		m_idleAnimation;
		

		sf::Texture		m_texture;
		sf::Texture		m_textureIdle;
		sf::Texture		m_textureWalk;
		sf::Texture		m_textureAttack;
		sf::Texture		m_textureHurt;
		sf::Texture		m_textureDie;
		sf::Texture		m_redBloodTexture;
		sf::Texture		m_greenBloodTexture;

		AnimatedSprite	m_animatedSpriteBlood;
		Animation		m_bloodAnimation;
		bool			m_drawBlood;

		sf::Time		m_deadTime;
		sf::Time		m_elapsedDeadTime;

		Direction		m_direction;
		Direction		m_prevDirection;
		sf::Vector2f	m_position;
		sf::Vector2f	m_prevPosition;
		float			m_velocity;

		float			m_health;
		float			m_maxHealth;
		uint			m_strength;
		uint			m_evasion;
		uint			m_level;
		bool			m_alive;
		bool			m_active;
	};
}