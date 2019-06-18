// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include "../lib.h"

#include "../Engine/engine.h"
#include "../Engine/Input/mouse.h"
#include "../Engine/Math/math.h"
#include "../Graphics/sprite.h"

struct Player {

	/*
	Struct containing all player data.
	*/
	
	std::atomic<bool> Ready;
	std::atomic<const char*> cc_ViableSquares;
	std::vector<std::string> ViableSquareIDs;
};

class GridSquare {

public:

	GridSquare(std::string path, std::string _id, glm::vec3 _position, float _scale = 1.0f);

	void Render() const;

	std::string GetID() const;
	Rect::XYWH GetRect() const;
	
	Image* GetImage();
	glm::vec3* GetPosition();

private:

	const std::string id;

	Image iGridSquare;
	Rect::XYWH rect;
};

class Grid {

public:

	Grid();

	void Update();
	void Render() const; // Debug

	std::vector<GridSquare> GetGrid() const;

private:

	std::vector<GridSquare> vGrid;
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
