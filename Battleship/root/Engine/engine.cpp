// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "engine.h"

#include "Input/mouse.h"
#include "Input/keyboard.h"

Engine::Engine() {};
Engine::~Engine() {};

int Engine::SCREEN_WIDTH = 650;
int Engine::SCREEN_HEIGHT = 600;

GLFWwindow* Engine::window = NULL;

bool Engine::init(char* windowTitle) {

	// Initialize GLFW
	if (!glfwInit()) {
		Misc::Logger("000e", "Error: Failed to initialize GLFW [glfwInit() = false].");
		return false;
	} 
	else {
		Misc::Logger("001e", "Successfully initialized GLFW [glfwInit() = true].");
	}

	// Create Window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
	if (window == NULL) {
		Misc::Logger("002e", "Error: Failed to create window [window = NULL].");
		return false;
	}
	else {
		Misc::Logger("003e", "Successfully created window [window != NULL].");
	}

	// GLFW Setup
	glfwMakeContextCurrent(window);
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(1);

	glfwSetCursorPosCallback(window, Mouse::MousePosCallback);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);

	glfwSetKeyCallback(window, Keyboard::KeyCallback);
	glfwSetCharCallback(window, Keyboard::CharCallback);

	// Window Setup
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos = (mode->width - SCREEN_WIDTH) / 2;
	int yPos = (mode->height - SCREEN_HEIGHT) / 2;
	glfwSetWindowPos(window, xPos, yPos);

	// Camera Setup
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);

	// Alpha Blending
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Engine::Update() const {
	Misc::UpdateDeltaTime();
	glfwPollEvents();
}

void Engine::BeginRender() const {
	glClearColor(1.0f, 1.0f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Engine::EndRender() const { glfwSwapBuffers(window); }

GLFWwindow* Engine::GetWindow() const { return window; }
