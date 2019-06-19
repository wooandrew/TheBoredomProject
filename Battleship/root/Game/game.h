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

#include "player.h"

class GridSquare {

public:

	GridSquare(std::string path, std::string _id, glm::vec3 _position, float _scale = 1.0f);

	void Render() const;

	std::string GetID() const;
	Rect::XYWH GetRect() const;
	
	Image* GetImage();
	glm::vec3* GetPosition();

	friend bool operator==(const GridSquare& left, const GridSquare& right);

private:

	Image iGridSquare;
	Rect::XYWH rect;

protected:

	const std::string id;
};

class Grid {

public:

	Grid(int GridSize = 40);

	void Update();
	void Render(bool debug = false) const; // Debug
	void Reset();

	void MakeIllegal(GridSquare square);
	void MakeLegal(GridSquare square);
	bool IsLegal(GridSquare square);

	std::vector<GridSquare> GetGrid() const;
	std::pair<Image, Rect::XYWH> GetGridSpace() const;
	std::list<GridSquare> GetIllegalSquares() const;
	std::string GetPressedSquare() const;
	
	friend void PrintIllegalSquares(Grid _grid); // Debug

private:

	std::vector<GridSquare> vGrid;
	std::pair<Image, Rect::XYWH> GridSpace;

protected:

	std::list<GridSquare> IllegalSquares;
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

std::pair<std::string, std::string> ParseRecvData(const char* ccRecvData);
void ParseRecvData(Player& player, const char* ccRecvData);

#endif // !BATTLESHIP_GAME
