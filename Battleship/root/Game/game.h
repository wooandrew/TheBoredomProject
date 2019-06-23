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

	GridSquare();
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
	const std::string id;
};

class Grid {

public:

	Grid(float GridSize = 40);

	void Update();
	void Render(bool debug = false) const; // Debug
	void Reset();

	void MakeIllegal(GridSquare square);
	void MakeLegal(GridSquare square);
	bool IsLegal(GridSquare square);

	std::vector<GridSquare> GetGrid() const;
	std::pair<Image, Rect::XYWH> GetGridSpace() const;
	std::list<GridSquare> GetIllegalSquares() const;
	GridSquare GetPressedSquare() const;
	
	friend void PrintIllegalSquares(Grid _grid); // Debug

private:

	std::vector<GridSquare> vGrid;
	std::pair<Image, Rect::XYWH> GridSpace;
	std::list<GridSquare> IllegalSquares;
};

class Pin {

public:

	Pin(GridSquare gs, bool _hit = false);

	void Render() const;

private:

	Image iPin;
	const std::string GridSquareID;
};

struct Attack {

	Attack();

	void Render();
	void Reset();

	void AttackSquare(GridSquare _gridsquare, bool goodhit = false);

	int GetGoodHitNum() const;
	std::vector<GridSquare> GetAttacked() const;

private:

	int goodhitnum;

	std::vector<GridSquare> Attacked;
	std::vector<Pin> pins;
};

namespace MiscGameObjects {

	const enum struct GameState {

		HOMESCREEN,
		TRYCONNECT,
		CONNECTFAIL,
		PLAYGAME,
		GAMEOVER,
		RESET,
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

GridSquare IDtoGR(Grid& _grid, std::string _id);

#endif // !BATTLESHIP_GAME
