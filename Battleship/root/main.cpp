// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "lib.h"

#include "Engine/engine.h"
#include "Graphics/sprite.h"

int main() {

	// *** Event Log *** START ******************************************** *** //
	system("TITLE Battleship Debug Console");
	//std::string logname = "battleship.logx"
	//std::ifstream gameLogExist(logname);
	//if (!gameLogExist) {
	//	std::ofstream log(logname);
	//	log << logname << " | Battleship GAME LOG generated @ " << GetDateTime() << std::endl;
	//	log.close();
	//}
	//gameLogExist.close();
	//
	//std::ofstream log(logname, std::ios_base::app);
	//std::cerr.rdbuf(log.rdbuf());
	std::cerr << "----------------------------------------------------------------------------" << std::endl;
	std::cerr << Misc::GetDateTime() << " |000x| PROGRAM STARTED." << std::endl;

	// *** Initialize Engine *** START ************************************ *** //
	Engine engine;
	if (engine.init() == false) {
		std::cerr << Misc::GetDateTime() << " |006e| Fatal Error: Could not initialize game engine." << std::endl;
		return -1;
	}
	// *** Initialize Engine *** END ************************************** *** //

	Sprite sprt("Assets\\Sprites\\test.png", glm::vec3(300, 300, 0));

	// *** Main Loop *** START *** **************************************** *** //
	while (!glfwWindowShouldClose(engine.GetWindow())) {

		// Update Events
		engine.Update();

		// Render
		engine.BeginRender();

		sprt.Render();

		engine.EndRender();
	}
	// *** Main Loop *** END *** ****************************************** *** //

	// *** Cleanup *** **************************************************** *** //
	std::cerr << Misc::GetDateTime() << " |001x| PROGRAM TERMINATED." << std::endl;

	glfwTerminate();

	return 0;
}
