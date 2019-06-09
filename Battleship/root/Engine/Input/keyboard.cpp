// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "keyboard.h"

std::vector<char> Keyboard::keysPressed;

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysDown[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysUp[GLFW_KEY_LAST] = { 0 };

void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers) {

	if (key < 0) { 
		return;
	}

	if (action != GLFW_RELEASE && keys[key] == false) {

		keysDown[key] = true;
		keysUp[key] = false;

		if (key == 259) {
			
			if (keysPressed.size() > 0) {
				keysPressed.pop_back();
			}
		}
		else {

			if (key != 257) {
				keysPressed.push_back(key);
				std::cout << key << std::endl;
			}
		}
	}

	if (action == GLFW_RELEASE && keys[key] == true) {
		keysDown[key] = false;
		keysUp[key] = true;
	}

	keys[key] = action != GLFW_RELEASE;
}

bool Keyboard::KeyDown(int key) {

	bool x = keysDown[key];
	keysDown[key] = false;
	
	return x;
}

bool Keyboard::KeyUp(int key) {

	bool x = keysUp[key];
	keysUp[key] = false;
	
	return x;
}

bool Keyboard::KeyIsPressed(int key) { 
	return keys[key];
}

std::vector<char> Keyboard::GetKeysPressed() {
	return keysPressed;
}

void Keyboard::ResetKeysPressed() {
	keysPressed.clear();
}
