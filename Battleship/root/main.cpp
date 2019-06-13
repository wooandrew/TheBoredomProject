// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "Connect/connect.h"

#include "lib.h"

#include "Game/game.h"

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
		log << logname << " | Battleship GAME LOG generated @ " << Utilities::GetDateTime() << std::endl;
		log.close();
	}
	gameLogExist.close();
	
	std::ofstream log(logname, std::ios_base::app);
	std::cerr.rdbuf(log.rdbuf());
	Utilities::Logger("----------------------------------------------------------------------------");
	Utilities::Logger("000x", "PROGRAM STARTED.");
	// *** Event Log *** END ********************************************** *** //

	// *** Initialize Engine *** START ************************************ *** //
	Engine engine;
	if (engine.init() == false) {
		Utilities::Logger("004e", "Fatal Error: Could not initialize game engine.");
		return -1;
	}
	else {
		Utilities::Logger("005e", "Successfully initialized game engine.");
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

	MGO::GameState CURRENTSTATE = MGO::GameState::HOMESCREEN;
	MGO::PlayState PLAYSTATE = MGO::PlayState::SETUP;

	host = false;

	// Utilities::GameState::HOMESCREEN objects
	Image homescreen("Assets/Screens/homescreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Button playbutton("Assets/Buttons/playbutton.png", glm::vec3(Engine::SCREEN_WIDTH + 130, 100, 0), 0.6f, MGO::GameState::TRYCONNECT, true);
	Button exitbutton("Assets/Buttons/exitbutton.png", glm::vec3(Engine::SCREEN_WIDTH + 130, 40, 0), 0.6f, MGO::GameState::EXIT, true);
	Button backbutton("Assets/Buttons/backbutton.png", glm::vec3(-130, Engine::SCREEN_HEIGHT - 49, 0), 0.6f, MGO::GameState::HOMESCREEN, true);

	// Utilities::GameState::TRYCONNECT objects
	Image connectscreen("Assets/Screens/connectscreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Button hostbutton("Assets/Buttons/host.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0), 1.0f, true);
	Button connectbutton("Assets/Buttons/connect.png", glm::vec3(Engine::SCREEN_WIDTH / 2, 95, 0), 1.0f, false);
	Textbox tbipaddr("Assets/Textboxes/ipaddr.png", glm::vec3(200, 170, 0), 1.0f);
	Textbox tbport("Assets/Textboxes/port.png", glm::vec3(Engine::SCREEN_WIDTH - 130.5, 170, 0), 1.0f);

	// Utilities::GameState::PLAYGAME objects
	Image pSetup("Assets/Screens/setup.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	//Convert Sprites -> Pieces
	Sprite Carrier("Assets/Sprites/carrier.png", glm::vec3(545, 530, 0));
	Sprite Cruiser("Assets/Sprites/cruiser.png", glm::vec3(545, 495, 0));
	Sprite Destroyer1("Assets/Sprites/destroyer.png", glm::vec3(545, 460, 0));
	Sprite Destroyer2("Assets/Sprites/destroyer.png", glm::vec3(545, 425, 0));
	Sprite Supply("Assets/Sprites/supply.png", glm::vec3(545, 390, 0));
	Sprite Submarine("Assets/Sprites/submarine.png", glm::vec3(545, 355, 0));

	// *** Main Loop *** START *** **************************************** *** //
	while (run) {

		if (glfwWindowShouldClose(engine.GetWindow())) {
			CURRENTSTATE = MGO::GameState::EXIT;
		}

		// Update Events
		engine.Update();

		// Render
		engine.BeginRender();
		switch (CURRENTSTATE) {

			case MGO::GameState::HOMESCREEN:
			{
				CURRENTSTATE = playbutton.Update(CURRENTSTATE, Engine::SCREEN_WIDTH + 130, Engine::SCREEN_WIDTH - 65);
				CURRENTSTATE = exitbutton.Update(CURRENTSTATE, Engine::SCREEN_WIDTH + 130, Engine::SCREEN_WIDTH - 65);

				homescreen.Render();
				playbutton.Render();
				exitbutton.Render();				

				break;
			}
			case MGO::GameState::TRYCONNECT:
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

				backbutton.Render();
				hostbutton.Render();
				connectbutton.Render();

				tbipaddr.Render(std::ref(abel), 46);
				tbport.Render(std::ref(abel), 46);

				if (retSocket._Is_ready()) {

					gSocket = retSocket.get();

					if (gSocket != INVALID_SOCKET) {

						CURRENTSTATE = MGO::GameState::PLAYGAME;
						PLAYSTATE = MGO::PlayState::SETUP;

						tRecvLoop = std::thread(Connect::RecvData, std::ref(run), std::ref(gSocket));

						connecting = false;
						connected = true;
					}
					else {

						CURRENTSTATE = MGO::GameState::CONNECTFAIL;

						retSocket.~future();

						connecting = false;
						connected = false;
					}
				}

				break;
			}
			case MGO::GameState::CONNECTFAIL:
			{
				CURRENTSTATE = MGO::GameState::HOMESCREEN;
				std::cout << "CONNECT FAIL" << std::endl;
				break;
			}
			case MGO::GameState::PLAYGAME:
			{
				if (gSocket != INVALID_SOCKET) {

					switch (PLAYSTATE) {

						case MGO::PlayState::SETUP:
						{
							pSetup.Render();

							Carrier.Render();
							Cruiser.Render();
							Destroyer1.Render();
							Destroyer2.Render();
							Supply.Render();
							Submarine.Render();

							break;
						}
						case MGO::PlayState::P1TURN:
							break;
						case MGO::PlayState::P2TURN:
							break;
						default:
						{
							PLAYSTATE = MGO::PlayState::SETUP;
							break;
						}							
					}
				}
				else {
					CURRENTSTATE = MGO::GameState::GAMEOVER;
					fDisconnect = true;
				}

				break;
			}
			case MGO::GameState::GAMEOVER:
			{
				if (gSocket != INVALID_SOCKET) {
					Connect::disconnect(std::ref(gSocket));
				}

				CURRENTSTATE = MGO::GameState::HOMESCREEN;
				connected = false;

				break;
			}
			case MGO::GameState::EXIT:
			{
				if (gSocket != INVALID_SOCKET) {
					Connect::disconnect(gSocket);
				}

				run = false;
				connected = false;

				break;
			}
			default:
			{
				CURRENTSTATE = MGO::GameState::HOMESCREEN;
				break;
			}
		}

		engine.EndRender();
	}
	// *** Main Loop *** END *** ****************************************** *** //

	// *** Cleanup *** **************************************************** *** //
	Utilities::Logger("001x", "Closed OpenGL window [glfwWindowShouldClose() = true].");
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

	Utilities::Logger("002x", "PROGRAM TERMINATED.");
	log.close();

	return 0;
}
