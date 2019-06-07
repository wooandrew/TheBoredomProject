// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef GAME_ENGINE
#define GAME_ENGINE

#include "../lib.h"

class Engine {

public:

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	Engine();
	~Engine();

	bool init(char* windowTitle = const_cast<char*>("Battleship"));

	void Update() const;
	void BeginRender() const;
	void EndRender() const;

	GLFWwindow* GetWindow() const;

private:
	static GLFWwindow* window;

};

#endif
