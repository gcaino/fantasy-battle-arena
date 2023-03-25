#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// -----------------------------------------
#include "AnimatedSprite.h"
#include "Animation.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
// -----------------------------------------
class Character : public GameObject
{
protected:
	enum DirectionAxis
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	struct Direction
	{
		DirectionAxis	_axisX;
		DirectionAxis	_axisY;
	};

	AnimatedSprite		_animatedSprite;

	Animation			_walkingAnimation;
	Animation			_attackAnimation;
	Animation			_hurtAnimation;
	Animation			_dieAnimation;
	Animation			_idleAnimation;
	Animation*			_currentAnimation;

	sf::Texture			_texture;
	sf::Texture			_textureIdle;
	sf::Texture			_textureWalk;
	sf::Texture			_textureAttack;
	sf::Texture			_textureHurt;
	sf::Texture			_textureDie;
	sf::Texture			_redBloodTexture;
	sf::Texture			_greenBloodTexture;

	AnimatedSprite		_animatedSpriteBlood;
	Animation			_bloodAnimation;
	bool				_drawBlood;

	sf::Time			_deadTime;
	sf::Time			_elapsedDeadTime;

	Direction			_direction;
	Direction			_prevDirection;
	sf::Vector2f		_position;
	sf::Vector2f		_prevPosition;
	float				_velocity;

	float				_health;
	float				_maxHealth;
	uint				_strength;
	uint				_evasion;
	uint				_level;
	bool				_alive;
	bool				_active;

public:
	Character();
	virtual ~Character();

	AnimatedSprite	getAnimatedSprite() const					{ return _animatedSprite; }
	AnimatedSprite	getAnimatedSpriteBlood() const				{ return _animatedSpriteBlood; }
	bool			canDrawBlood() const						{ return _drawBlood; }
	void			setDrawBlood(bool drawBlood)				{ _drawBlood = drawBlood; }
	sf::Vector2f	getPosition() const							{ return _position; }
	void			setPosition(sf::Vector2f newPosition)		{ _position = newPosition; }
	void			setPosition(float x, float y)				{ _position.x = x; _position.y = y; }
	Direction		getDirection() const						{ return _direction; }
	void			setDirection(Direction newDirection)		{ _direction = newDirection; }
	sf::Vector2f	getPrevPosition() const						{ return _prevPosition; }
	void			setPrevPosition(sf::Vector2f prevPosition)	{ _position = prevPosition; }
	bool			isAlive() const								{ return _alive; }
	void			setAlive(bool alive)						{ _alive = alive; }
	bool			isActive() const							{ return _active; }
	void			setActive(bool active)						{ _active = active; }
	float			getHealth() const							{ return _health; }
	float			getMaxHealth() const						{ return _maxHealth; }
	float			getVelocity() const							{ return _velocity; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	void calculateDirection();
	void rotateSprite();
};
// -----------------------------------------
}
// -----------------------------------------
#endif // GAMEOBJECT_H