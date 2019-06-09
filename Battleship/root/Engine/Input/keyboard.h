// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef ENGINE_INPUT_KEYBOARD
#define ENGINE_INPUT_KEYBOARD

#include "../../lib.h"

class Keyboard {

public:

	Keyboard() = delete;

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);

	static bool KeyDown(int key);
	static bool KeyUp(int key);
	static bool KeyIsPressed(int key);

	static std::vector<char> GetKeysPressed();
	static void ResetKeysPressed();

	static std::vector<char> keysPressed;

private:

	static bool keys[];
	static bool keysDown[];
	static bool keysUp[];
};

#endif // !ENGINE_INPUT_KEYBOARD

