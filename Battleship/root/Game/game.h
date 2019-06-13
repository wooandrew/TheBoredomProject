// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

class Grid {

public:

	Grid();

private:

};

namespace MiscGameObjects {

	const enum struct GameState {

		HOMESCREEN,
		TRYCONNECT,
		CONNECTFAIL,
		PLAYGAME,
		GAMEOVER,
		EXIT
	};

	const enum struct PlayState {

		SETUP,
		P1TURN,
		P2TURN
	};
}

namespace MGO = MiscGameObjects;

#endif // !BATTLESHIP_GAME
