// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef ENGINE_INPUT_MOUSE
#define ENGINE_INPUT_MOUSE

#include "../../lib.h"

class Mouse {

public:

	Mouse() = delete;

	static void MousePosCallback(GLFWwindow* window, double _x, double _y);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);

	static double GetMouseX();
	static double GetMouseY();

	static bool ButtonDown(int button);
	static bool ButtonUp(int button);
	static bool ButtonIsPressed(int button);

private:

	static double x;
	static double y;

	static bool buttons[];
	static bool buttonsDown[];
	static bool buttonsUp[];
};

#endif // !ENGINE_INPUT_MOUSE
