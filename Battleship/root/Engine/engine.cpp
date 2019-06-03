// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "engine.h"

int Engine::WINDOW_WIDTH = 1300;
int Engine::WINDOW_HEIGHT = 650;

int Engine::frameBufferWidth = 0;
int Engine::frameBufferHeight = 0;

GLFWwindow* Engine::window = NULL;

Engine::Engine() {}
Engine::~Engine() {}

void Engine::frameBufferResizeCallback(GLFWwindow* window, int _frameBufferWidth, int _frameBufferHeight) {

	glViewport(0, 0, _frameBufferWidth, _frameBufferHeight);
}

bool Engine::init(char* windowTitle) {

	// *** GLFW Initialization *** START ********************************** *** //
	if (!glfwInit()) {
		std::cerr << Misc::GetDateTime() << " |000e| Fatal Error: Failed to initialize GLFW [glfwInit() = false]." << std::endl;
		return false;
	}
	else {
		std::cerr << Misc::GetDateTime() << " |001e| Successfully initialized GLFW [glfwInit() = true]." << std::endl;
	}
	// *** GLFW Initialization *** END ************************************ *** //

	// *** GLFW Window Creation *** START ********************************* *** //
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle, NULL, NULL);
	if (window == NULL) {
		std::cerr << Misc::GetDateTime() << " |002e| Fatal Error: Failed to create window [window = NULL]." << std::endl;
		return false;
	}
	else {
		std::cerr << Misc::GetDateTime() << " |003e| Successfully created window [window != NULL]" << std::endl;
	}

	glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
	// when GLFW_RESIZABLE = GL_TRUE ::: glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	// when GLFW_RESIZABLE = GL_TRUE ::: glViewport(0, 0, frameBufferWidth, frameBufferHeight);

	glfwMakeContextCurrent(window); // CRITICAL
	// *** GLFW Window Creation *** END *********************************** *** //

	// *** GLEW Initialization *** START ********************************** *** //
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {

		glfwTerminate(); // Terminates GLFW
		std::cerr << Misc::GetDateTime() << " |004e| Fatal Error: Failed to initialize GLEW [glewInit() = false]." << std::endl;

		return false;
	}
	else {
		std::cerr << Misc::GetDateTime() << " |005e| Successfully initialized GLEW [glewInit() = true]." << std::endl;
	}
	// *** GLEW Initialization *** END ************************************ *** //

	// *** OpenGL Options *** START *************************************** *** //
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// *** OpenGL Options *** END ***************************************** *** //

	return true;
}

void Engine::Update() const {
	glfwPollEvents();
}

void Engine::BeginRender() const {
	glClearColor(1.0f, 1.0f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Engine::EndRender() const {
	glfwSwapBuffers(window);
	glFlush();
}

GLFWwindow* Engine::GetWindow() const { return window; }
