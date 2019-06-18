// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef CSG_SHIP
#define CSG_SHIP

#include "../lib.h"

#include "../Engine/engine.h"
#include "../Engine/Input/mouse.h"
#include "../Engine/Input/keyboard.h"
#include "../Engine/Math/math.h"

#include "../Graphics/sprite.h"

#include "../Game/game.h"

const enum struct ShipType {

	AircraftCarrier,
	Cruiser,
	Destroyer,
	Supply,
	Submarine
};

class Ship {

public:

	Ship(std::string path, ShipType _type, glm::vec3 _position, float _scale = 1.0f);
	Ship(Image& _iShip, ShipType _type);

	void Update(Grid& _grid, bool setup = false);
	void Render() const;

	void UpdateRect();
	bool GetPlaced() const;

private:

	Image iShip;

	bool selected;
	bool placed;

	Rect::XYWH rect;

	const ShipType type;
	const glm::vec3 defaultPosition;
};

#endif // !CSG_SHIP

