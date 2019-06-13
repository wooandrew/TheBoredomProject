// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef CSG_SHIP
#define CSG_SHIP

#include "../lib.h"

#include "../Engine/engine.h"
#include "../Engine/Input/mouse.h"
#include "../Engine/Math/math.h"

#include "../Graphics/sprite.h"

class Ship {

public:
	
	Ship(std::string path, glm::vec3 _position, float _scale = 1.0f);
	Ship(Image& _iShip);

	void Update(bool setup = false);
	void Render() const;

	void UpdateRect();

private:

	Image iShip;

	bool selected;
	Rect::XYWH rect;

	const glm::vec3 defaultPosition;
};

#endif // !CSG_SHIP

