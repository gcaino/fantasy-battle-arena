#pragma once
// -----------------------------------------
namespace lpa
{
	class InputManager
	{
	public:
		InputManager();

		void moveUp()		{ m_upPressed    = true; }
		void moveDown()		{ m_downPressed  = true; }
		void moveLeft()		{ m_leftPressed  = true; }
		void moveRigth()	{ m_rightPressed = true; }

		void stopUp()		{ m_upPressed    = false; }
		void stopDown()		{ m_downPressed  = false; }
		void stopLeft()		{ m_leftPressed  = false; }
		void stopRigth()	{ m_rightPressed = false; }

	protected:
		bool m_upPressed;
		bool m_downPressed;
		bool m_leftPressed;
		bool m_rightPressed;
	};
}

