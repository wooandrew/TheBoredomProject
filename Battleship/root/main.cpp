// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "Connect/connect.h"
#include "lib.h"

#include "Engine/engine.h"
#include "Engine/Input/mouse.h"
#include "Graphics/sprite.h"

int main() {

	// *** Event Log *** START ******************************************** *** //
	system("TITLE Battleship Debug Console");
	std::string logname = "battleship.logx";
	std::ifstream gameLogExist(logname);
	if (!gameLogExist) {

		std::ofstream log(logname);
		log << logname << " | Battleship GAME LOG generated @ " << Misc::GetDateTime() << std::endl;
		log.close();
	}
	gameLogExist.close();
	
	std::ofstream log(logname, std::ios_base::app);
	std::cerr.rdbuf(log.rdbuf());
	Misc::Logger("----------------------------------------------------------------------------");
	Misc::Logger("000x", "PROGRAM STARTED.");
	// *** Event Log *** END ********************************************** *** //

	// *** Initialize Engine *** START ************************************ *** //
	Engine engine;
	if (engine.init() == false) {
		Misc::Logger("004e", "Fatal Error: Could not initialize game engine.");
		return -1;
	}
	else {
		Misc::Logger("005e", "Successfully initialized game engine.");
	}
	// *** Initialize Engine *** END ************************************** *** //

	// *** Pseudo-Global Variables *** START ****************************** *** //
	bool run = true;
	bool host = false;
	bool connected = false;
	bool connecting = false;
	bool fDisconnect = false;
	// *** Pseudo-Global Variables *** END ******************************** *** //

	// *** Connection Initializer *** START ******************************* *** //
	SOCKET gSocket = INVALID_SOCKET;
	std::future<SOCKET> retSocket;
	std::thread tRecvLoop;
	// *** Connection Initializer *** END ********************************* *** //

	Misc::GameState CURRENTSTATE = Misc::GameState::HOMESCREEN;

	host = true;

	Sprite testsprt("Assets/Sprites/test2.png", glm::vec3(300, 300, 0));
	Sprite testsprt2("Assets/Sprites/test.png", glm::vec3(300, 500, 0), 0.3f);

	// *** Main Loop *** START *** **************************************** *** //
	while (run) {

		if (glfwWindowShouldClose(engine.GetWindow())) {

			if (retSocket.valid()) {
				retSocket.get();
				retSocket.~future();
			}
			else {
				retSocket.~future();
			}
			
			if (gSocket != INVALID_SOCKET) {
				Connect::disconnect(gSocket);
				gSocket = INVALID_SOCKET;
			}
			
			run = false;
			connected = false;

			break;
		}

		// Update Events
		engine.Update();

		// Render
		engine.BeginRender();
		switch (CURRENTSTATE) {

			case Misc::GameState::HOMESCREEN:
			{
				CURRENTSTATE = Misc::GameState::TRYCONNECT;
				break;
			}
			case Misc::GameState::TRYCONNECT:
			{
				if (!connecting && !connected) {
					retSocket = std::async(std::launch::async, Connect::connect, host, "127.0.0.1", "30980");
					connecting = true;
				}

				if (retSocket._Is_ready()) {

					gSocket = retSocket.get();

					if (gSocket != INVALID_SOCKET) {
					
						CURRENTSTATE = Misc::GameState::PLAYGAME;

						tRecvLoop = std::thread(Connect::RecvData, std::ref(run), std::ref(gSocket));

						connecting = false;
						connected = true;
					}
					else {

						CURRENTSTATE = Misc::GameState::CONNECTFAIL;

						connecting = false;
						connected = false;
					}
				}

				break;
			}
			case Misc::GameState::CONNECTFAIL:
			{
				CURRENTSTATE = Misc::GameState::HOMESCREEN;
				std::cout << "CONNECT FAIL" << std::endl;
				break;
			}
			case Misc::GameState::PLAYGAME:
			{
				if (gSocket != INVALID_SOCKET) {

					if (Mouse::GetMouseX() > 300 && connected) {
						Connect::SendData(std::ref(gSocket), "data\n");
					}
				}
				else {
					CURRENTSTATE = Misc::GameState::GAMEOVER;
					fDisconnect = true;
				}

				break;
			}
			case Misc::GameState::GAMEOVER:
			{
				if (gSocket != INVALID_SOCKET) {
					Connect::disconnect(std::ref(gSocket));
				}
				break;
			}
			case Misc::GameState::EXIT:
			{
				if (gSocket != INVALID_SOCKET) {
					Connect::disconnect(std::ref(gSocket));
				}

				run = false;
				break;
			}
		}

		engine.EndRender();
	}
	// *** Main Loop *** END *** ****************************************** *** //

	if (tRecvLoop.joinable()) {
		tRecvLoop.join();
	}

	// *** Cleanup *** **************************************************** *** //
	Misc::Logger("001x", "Closed OpenGL window [glfwWindowShouldClose() = true].");
	Misc::Logger("002x", "PROGRAM TERMINATED.");

	glfwTerminate();
	log.close();

	return 0;
}
