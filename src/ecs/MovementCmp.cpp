#include "pch.h"
#include "MovementCmp.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	MovementCmp::MovementCmp()
		: position{}
		, prevPosition{}
		, velocity{}
		, currentDirection{ AxisDirection::None, AxisDirection::None }
		, prevDirection	  { AxisDirection::None, AxisDirection::None }
	{
	}

	void MovementCmp::calculateDirection()
	{
		if		(position.x > prevPosition.x) currentDirection.xAxis = AxisDirection::Right;
		else if (position.x < prevPosition.x) currentDirection.xAxis = AxisDirection::Left;
		else if	(position.y > prevPosition.y) currentDirection.yAxis = AxisDirection::Down;
		else if (position.y < prevPosition.y) currentDirection.yAxis = AxisDirection::Up;
	}

	void MovementCmp::setPreviousDirection()
	{
		if	(currentDirection.xAxis != prevDirection.xAxis)
			 prevDirection.xAxis  = currentDirection.xAxis;

		if (currentDirection.yAxis != prevDirection.yAxis)
			prevDirection.yAxis = currentDirection.yAxis;
	}
}
