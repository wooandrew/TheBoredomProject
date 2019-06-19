// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef GAME_PLAYER
#define GAME_PLAYER

#include <atomic>
#include <string>
#include <vector>

struct Player {

	/*
	Struct containing all player data.
	*/

	std::atomic<bool> Ready;
	std::vector<std::string> ShipPlaced;
	std::vector<std::string> ViableSquareIDs;
	std::vector<std::string> PlacedIDs;
	std::vector<std::string> ShipRotations;		// Currently Unused
};

#endif // !GAME_PLAYER
