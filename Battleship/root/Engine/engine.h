// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef ENGINE
#define ENGINE

#include "../lib.h"

class Engine {

public:

	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;

	static int frameBufferWidth;
	static int frameBufferHeight;
	static void frameBufferResizeCallback(GLFWwindow* window, int _frameBufferWidth, int _frameBufferHeight);

	Engine();
	~Engine();

	void Update() const;
	void BeginRender() const;
	void EndRender() const;

	static bool init(char* windowTitle = const_cast<char*>("Battleship"));
	GLFWwindow* GetWindow() const;

private:
	static GLFWwindow* window;
};

#endif // !ENGINE
