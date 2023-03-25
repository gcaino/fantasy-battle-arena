#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
class InputManager
{
protected:
	bool _upPressed;
	bool _downPressed;
	bool _leftPressed;
	bool _rightPressed;

public:
	InputManager();
	~InputManager();

	void moveUp() { _upPressed = true; }
	void moveDown() { _downPressed = true; }
	void moveLeft() { _leftPressed = true; }
	void moveRigth() { _rightPressed = true; }

	void stopUp() { _upPressed = false; }
	void stopDown() { _downPressed = false; }
	void stopLeft() { _leftPressed = false; }
	void stopRigth() { _rightPressed = false; }
};
// -----------------------------------------
}
// -----------------------------------------
#endif // !INPUT_MANAGER_H
