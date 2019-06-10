// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "Connect/connect.h"
#include "lib.h"

#include "Engine/engine.h"
#include "Engine/Input/mouse.h"
#include "Engine/Input/keyboard.h"
#include "Engine/Input/button.h"
#include "Engine/Input/textbox.h"

#include "Graphics/text.h"
#include "Graphics/sprite.h"

// RULE: Host goes first.

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

	Text abel;
	abel.LoadFont("Assets/Fonts/abel.ttf", 46);

	Misc::GameState CURRENTSTATE = Misc::GameState::HOMESCREEN;

	host = false;

	Image homescreen("Assets/Screens/homescreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Button playbutton("Assets/Buttons/playbutton.png", glm::vec3(Engine::SCREEN_WIDTH + 130, 100, 0), 0.6f, Misc::GameState::TRYCONNECT, true);
	Button exitbutton("Assets/Buttons/exitbutton.png", glm::vec3(Engine::SCREEN_WIDTH + 130, 40, 0), 0.6f, Misc::GameState::EXIT, true);
	Button backbutton("Assets/Buttons/backbutton.png", glm::vec3(-130, Engine::SCREEN_HEIGHT - 49, 0), 0.6f, Misc::GameState::HOMESCREEN, true);

	Image connectscreen("Assets/Screens/connectscreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Button hostbutton("Assets/Buttons/host.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0), 1.0f, true);
	Button connectbutton("Assets/Buttons/connect.png", glm::vec3(Engine::SCREEN_WIDTH / 2, 95, 0), 1.0f, false);
	Textbox tbipaddr("Assets/Textboxes/ipaddr.png", glm::vec3(200, 170, 0), 1.0f);
	Textbox tbport("Assets/Textboxes/port.png", glm::vec3(Engine::SCREEN_WIDTH - 130.5, 170, 0), 1.0f);

	// *** Main Loop *** START *** **************************************** *** //
	while (run) {

		if (glfwWindowShouldClose(engine.GetWindow())) {
			
			CURRENTSTATE = Misc::GameState::EXIT;
		}

		// Update Events
		engine.Update();

		// Render
		engine.BeginRender();
		switch (CURRENTSTATE) {

			case Misc::GameState::HOMESCREEN:
			{
				CURRENTSTATE = playbutton.Update(CURRENTSTATE, Engine::SCREEN_WIDTH + 130, Engine::SCREEN_WIDTH - 65);
				CURRENTSTATE = exitbutton.Update(CURRENTSTATE, Engine::SCREEN_WIDTH + 130, Engine::SCREEN_WIDTH - 65);

				homescreen.Render();
				playbutton.GetImage().Render();
				exitbutton.GetImage().Render();				

				break;
			}
			case Misc::GameState::TRYCONNECT:
			{
				CURRENTSTATE = backbutton.Update(CURRENTSTATE, -130, 95);

				tbipaddr.Update();
				tbport.Update();

				host = hostbutton.Update(host);
				if (hostbutton.GetButtonPressed()) {

					if (!connecting && !connected) {
						retSocket = std::async(std::launch::async, Connect::connect, host, "", "30980");
						connecting = true;
					}
				}

				host = connectbutton.Update(host);
				if (connectbutton.GetButtonPressed()) {

					if (!connecting && !connected) {
						retSocket = std::async(std::launch::async, Connect::connect, host, tbipaddr.GetText(), tbport.GetText());
						connecting = true;
					}
				}

				connectscreen.Render();

				backbutton.GetImage().Render();
				hostbutton.GetImage().Render();
				connectbutton.GetImage().Render();

				tbipaddr.Render(std::ref(abel), 46);
				tbport.Render(std::ref(abel), 46);

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

						retSocket.~future();

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
					Connect::disconnect(gSocket);
				}

				run = false;
				connected = false;

				break;
			}
		}

		engine.EndRender();
	}
	// *** Main Loop *** END *** ****************************************** *** //

	// *** Cleanup *** **************************************************** *** //
	Misc::Logger("001x", "Closed OpenGL window [glfwWindowShouldClose() = true].");
	glfwTerminate();

	if (retSocket.valid()) {
		retSocket.get();
		retSocket.~future();
	}
	else {
		retSocket.~future();
	}

	if (tRecvLoop.joinable()) {
		tRecvLoop.join();
	}

	Misc::Logger("002x", "PROGRAM TERMINATED.");
	log.close();

	return 0;
}
