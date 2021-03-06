// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "Connect/connect.h"

#include "lib.h"

#include "Game/game.h"
#include "Game/player.h"

#include "Engine/engine.h"
#include "Engine/Input/mouse.h"
#include "Engine/Input/keyboard.h"
#include "Engine/Input/button.h"
#include "Engine/Input/textbox.h"

#include "Graphics/text.h"
#include "Graphics/sprite.h"

#include "CarrierStrikeGroup/carrierstrikegroup.h"

// RULE: Host goes first.

/** Versioning
 *
 * Types: b.BUILD r.RELEASE
 * Convention: type_commit_year
**/

constexpr auto build_version = "b11y19";
constexpr bool debug = false;

int main() {

	// *** Event Log *** START ******************************************** *** //
	system("TITLE Battleship Debug Console");

	if (!debug) {
		Utilities::DebugConsole::Hide();
	}
	else {
		Utilities::DebugConsole::DisableShowHide();
	}

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
	
	std::stringstream stream;
	stream << "----------------------------------------------------------------------------------------------------------------- " << build_version << " ----";
	
	Utilities::Logger(stream.str());
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

	// MiscGameObjects::GameState::HOMESCREEN objects
	Image homescreen("Assets/Screens/homescreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Button playbutton("Assets/Buttons/playbutton.png", glm::vec3(Engine::SCREEN_WIDTH + 130, 100, 0), 0.6f, MGO::GameState::TRYCONNECT, true);
	Button exitbutton("Assets/Buttons/exitbutton.png", glm::vec3(Engine::SCREEN_WIDTH + 130, 40, 0), 0.6f, MGO::GameState::EXIT, true);
	Button backbutton("Assets/Buttons/backbutton.png", glm::vec3(-130, Engine::SCREEN_HEIGHT - 49, 0), 0.6f, MGO::GameState::HOMESCREEN, true);
	Button backbuttonv("Assets/Buttons/backbutton.png", glm::vec3(-130, Engine::SCREEN_HEIGHT - 49, 0), 0.6f, MGO::GameState::RESET, true);

	// MiscGameObjects::GameState::TRYCONNECT objects
	Image connectscreen("Assets/Screens/connectscreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Button hostbutton("Assets/Buttons/hostbutton.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0), 1.0f, true);
	Button connectbutton("Assets/Buttons/connectbutton.png", glm::vec3(Engine::SCREEN_WIDTH / 2, 95, 0), 1.0f, false);
	Textbox tbipaddr("Assets/Textboxes/ipaddr.png", glm::vec3(200, 170, 0), 1.0f);
	Textbox tbport("Assets/Textboxes/port.png", glm::vec3(Engine::SCREEN_WIDTH - 130.5, 170, 0), 1.0f);

	// MiscGameObjects::GameState::PLAYGAME objects
	Image pSetup("Assets/Screens/setup.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Image pPlay1("Assets/Screens/play.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));

	Button readybutton("Assets/Buttons/readybutton.png", glm::vec3(90, 30, 0), 1.0f, false);
	Button notreadybutton("Assets/Buttons/notreadybutton.png", glm::vec3(90, 30, 0), 1.0f, true);
	Image ready("Assets/ready.png", glm::vec3(250, 138, 0));
	Image notready("Assets/notready.png", glm::vec3(250, 138, 0));

	std::vector<glm::vec3> SetupDefaultPositions;
	SetupDefaultPositions.push_back(glm::vec3(545, 530, 0));
	SetupDefaultPositions.push_back(glm::vec3(545, 495, 0));
	SetupDefaultPositions.push_back(glm::vec3(545, 460, 0));
	SetupDefaultPositions.push_back(glm::vec3(545, 425, 0));
	SetupDefaultPositions.push_back(glm::vec3(545, 390, 0));
	SetupDefaultPositions.push_back(glm::vec3(545, 355, 0));

	CSG csg_setup(SetupDefaultPositions);
	CSG full(SetupDefaultPositions, true);

	Grid SetupGrid;
	Grid PlayGrid(54.5);

	Attack p1attacks;
	Attack p2attacks;

	// Player Data
	Player player1;
	Player player2;

	player1.Ready = false;
	player2.Ready = false;

	std::string winner = "";

	// MiscGameObjects::GameState::GAMEOVER objects
	Image p1victory("Assets/Screens/p1victoryscreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	Image p2victory("Assets/Screens/p2victoryscreen.png", glm::vec3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));

	// *** Main Loop *** START *** **************************************** *** //
	while (run) {

		if (glfwWindowShouldClose(engine.GetWindow())) {
			CURRENTSTATE = MGO::GameState::EXIT;
		}

		if (Keyboard::KeyDown(GLFW_KEY_GRAVE_ACCENT)) {
			Utilities::DebugConsole::AutoShowHide();
		}

		// Update Events
		engine.Update();

		// Render
		engine.BeginRender();
		switch (CURRENTSTATE) {

			case MGO::GameState::HOMESCREEN:
			{
				winner = "";

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
						//catch(std::exception &e){
						//
						//	std::ostringstream stream;
						//	stream << "Error: exception [" << &e << "] occured.";
						//	Utilities::Logger(stream.str(), true);
						//}

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
							SetupGrid.Render();

							if (Connect::aRecvData != NULL) { // Parse Recieved Data
								ParseRecvData((host ? player2 : player1), Connect::aRecvData.load());
							}

							if (host) { // If host

								if (player1.Ready) { // Host is ready

									player1.Ready = readybutton.Update(player1.Ready);
									readybutton.Render();

									if (!player1.Ready) {
										Connect::SendData(std::ref(gSocket), "not_ready");
									}
								}
								else { // Host is not ready

									csg_setup.Update(SetupGrid, true);
									notreadybutton.Render();

									if (csg_setup.GetReady()) {
										player1.Ready = notreadybutton.Update(player1.Ready);
									}
									
									if (player1.Ready) {

										std::ostringstream stream;
										stream << "ready&illegal_squares";

										for (const GridSquare tGridSquare : SetupGrid.GetIllegalSquares()) {
											stream << ":" << tGridSquare.GetID();
										}

										stream << "&placed_ids:" << csg_setup.GetPlacedIDs() << "&csg_rotations:" << csg_setup.GetRotations();

										Connect::SendData(std::ref(gSocket), stream.str().c_str());
									}
								}

								if (player2.Ready) {
									ready.Render();
								}
								else {
									notready.Render();
								}
							}
							else { // If NOT host

								if (player2.Ready) { // Player 2 is ready

									player2.Ready = readybutton.Update(player2.Ready);
									readybutton.Render();

									if (!player2.Ready) {
										Connect::SendData(std::ref(gSocket), "not_ready");
									}
								}
								else { // Player 2 is not ready

									csg_setup.Update(SetupGrid, true);
									notreadybutton.Render();

									if (csg_setup.GetReady()) {
										player2.Ready = notreadybutton.Update(player2.Ready);
									}

									if (player2.Ready) {

										std::ostringstream stream;
										stream << "ready&illegal_squares";

										for (const GridSquare tGridSquare : SetupGrid.GetIllegalSquares()) {
											stream << ":" << tGridSquare.GetID();
										}

										stream << "&placed_ids:" << csg_setup.GetPlacedIDs() << "&csg_rotations:" << csg_setup.GetRotations();

										Connect::SendData(std::ref(gSocket), stream.str().c_str());
									}
								}

								if (player1.Ready) {
									ready.Render();
								}
								else {
									notready.Render();
								}
							}

							if (player1.Ready && player2.Ready) {

								PLAYSTATE = MGO::PlayState::P1TURN;
								full.Assemble(PlayGrid, csg_setup.GetPlacedIDs(), csg_setup.GetRotations());

								std::this_thread::sleep_for(std::chrono::seconds(2));
							}

							csg_setup.Render();

							break;
						}
						case MGO::PlayState::P1TURN:
						{
							pPlay1.Render();
							PlayGrid.Update();

							if (host) {

								GridSquare PressedGridSquare = PlayGrid.GetPressedSquare();
								bool AlreadyAttacked = false;

								for (const GridSquare gs : p1attacks.GetAttacked()) {
									
									if (gs == PressedGridSquare) {
										AlreadyAttacked = true;
										break;
									}
								}

								if (PressedGridSquare.GetID() != "NULL" && !AlreadyAttacked) {

									for (const std::string ID : player2.ViableSquareIDs) {

										if (ID == PressedGridSquare.GetID()) {
											p1attacks.AttackSquare(PressedGridSquare, true);
											break;
										}
									}

									p1attacks.AttackSquare(PressedGridSquare);

									PLAYSTATE = MGO::PlayState::P2TURN;
									Connect::SendData(std::ref(gSocket), ("attack:" + PressedGridSquare.GetID()).c_str());
								}

								p1attacks.Render();
							}
							else {

								full.Render();

								std::pair<std::string, std::string> RecvParsePair = ParseRecvData(Connect::aRecvData.load());

								if (RecvParsePair.first == "attack") {

									PLAYSTATE = MGO::PlayState::P2TURN;
									Connect::aRecvData.store("");

									p1attacks.AttackSquare(IDtoGR(PlayGrid, RecvParsePair.second), !SetupGrid.IsLegal(IDtoGR(SetupGrid, RecvParsePair.second)));
								}

								p1attacks.Render();
							}

							if (p1attacks.GetGoodHitNum() == 18 || p2attacks.GetGoodHitNum() == 18) {

								CURRENTSTATE = MGO::GameState::GAMEOVER;

								if (p1attacks.GetGoodHitNum() == 18) {
									winner = "p1";
								}
								else {
									winner = "p2";
								}
							}

							break;
						}
						case MGO::PlayState::P2TURN:
						{
							pPlay1.Render();
							PlayGrid.Update();

							if (!host) {

								GridSquare PressedGridSquare = PlayGrid.GetPressedSquare();
								bool AlreadyAttacked = false;

								for (const GridSquare gs : p2attacks.GetAttacked()) {

									if (gs == PressedGridSquare) {
										AlreadyAttacked = true;
										break;
									}
								}

								if (PressedGridSquare.GetID() != "NULL" && !AlreadyAttacked) {

									for (const std::string ID : player1.ViableSquareIDs) {

										if (ID == PressedGridSquare.GetID()) {
											p2attacks.AttackSquare(PressedGridSquare, true);
											break;
										}
									}

									p2attacks.AttackSquare(PressedGridSquare);

									PLAYSTATE = MGO::PlayState::P1TURN;
									Connect::SendData(std::ref(gSocket), ("attack:" + PressedGridSquare.GetID()).c_str());
								}

								p2attacks.Render();
							}
							else {

								full.Render();

								std::pair<std::string, std::string> RecvParsePair = ParseRecvData(Connect::aRecvData.load());

								if (RecvParsePair.first == "attack") {

									PLAYSTATE = MGO::PlayState::P1TURN;
									Connect::aRecvData.store("");

									p2attacks.AttackSquare(IDtoGR(PlayGrid, RecvParsePair.second), !SetupGrid.IsLegal(IDtoGR(SetupGrid, RecvParsePair.second)));
								}

								p2attacks.Render();
							}

							if (p1attacks.GetGoodHitNum() == 18 || p2attacks.GetGoodHitNum() == 18) {

								CURRENTSTATE = MGO::GameState::GAMEOVER;

								if (p1attacks.GetGoodHitNum() == 18) {
									winner = "p1";
								}
								else {
									winner = "p2";
								}
							}

							break;
						}
						default:
						{
							PLAYSTATE = MGO::PlayState::SETUP;
							break;
						}
					}
				}
				else {
					CURRENTSTATE = MGO::GameState::GAMEOVER;
				}

				break;
			}
			case MGO::GameState::GAMEOVER:
			{
				if (!host) {

					std::pair<std::string, std::string> temp = ParseRecvData(Connect::aRecvData.load());

					if (temp.first == "winner") {
						winner = temp.second;
					}
				}

				if (winner == "p1") {
					CURRENTSTATE = backbuttonv.Update(CURRENTSTATE, -130, 95);
					p1victory.Render();
				}
				else if (winner == "p2") {
					CURRENTSTATE = backbuttonv.Update(CURRENTSTATE, -130, 95);
					p2victory.Render();
				}
				else {

					CURRENTSTATE = backbuttonv.Update(CURRENTSTATE, -130, 95);

					if (p1attacks.GetGoodHitNum() == 18 || p2attacks.GetGoodHitNum() == 18) {

						if (p1attacks.GetGoodHitNum() == 18) {
							winner = "p1";
						}
						else {
							winner = "p2";
						}
					}
				}

				backbuttonv.Render();

				break;
			}
			case MGO::GameState::RESET:
			{
				if (gSocket != INVALID_SOCKET) {
					Connect::disconnect(std::ref(gSocket));
				}

				if (tRecvLoop.joinable()) {
					tRecvLoop.join();
				}
				tRecvLoop = std::thread();

				CURRENTSTATE = MGO::GameState::HOMESCREEN;
				PLAYSTATE = MGO::PlayState::SETUP;

				connected = false;
				connecting = false;

				player1.Ready = false;
				player2.Ready = false;

				p1attacks.Reset();
				p2attacks.Reset();

				SetupGrid.Reset();
				csg_setup.Reset();

				PlayGrid.Reset();
				full.Reset();

				Connect::aRecvData.store("");

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
	}

	if (tRecvLoop.joinable()) {
		tRecvLoop.join();
	}

	Utilities::Logger("002x", "PROGRAM TERMINATED.");
	//log.close(); // Remove 'cause RAII

	return 0;
}
