#pragma once
// --------------------------------------------------------------------------------
#include "pch.h"
#include "ecs\Component.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	enum class AxisDirection
	{
		None, Left, Right, Up, Down
	};

	struct Direction
	{
		AxisDirection xAxis;
		AxisDirection yAxis;
	};

	class MovementCmp : public Component
	{
	public:
		MovementCmp();

		void calculateDirection();
		void setPreviousDirection();

		sf::Vector2f	position;
		sf::Vector2f	prevPosition;
		float			velocity;
		Direction		currentDirection;
		Direction		prevDirection;
	};
}
