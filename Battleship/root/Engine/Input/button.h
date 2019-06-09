// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef ENGINE_INPUT_BUTTON
#define ENGINE_INPUT_BUTTON

#include "../../lib.h"
#include "../../Graphics/sprite.h"

#include "../engine.h"
#include "mouse.h"

struct Rect {

	friend std::ostream& operator<<(std::ostream& os, Rect right);

	float x;
	float y;
	float width;
	float height;
};

class Button {

public:

	Button(std::string path, glm::vec3 _position, float scale, Misc::GameState _retVal, bool _HideAwayButton = false);
	Button(Image& _buttonimage, Misc::GameState _retVal, bool _HideAwayButton = false);

	void HideAway(int xmax, int xmin, bool use = false);

	Misc::GameState Update(Misc::GameState currentstate, int xmax = Engine::SCREEN_WIDTH, int xmin = 0);
	void UpdateRect();

	Image GetImage() const;

private:

	bool buttonPressable;
	bool HideAwayButton;

	Misc::GameState retVal;

	Image buttonimage;
	Rect rect;
};

#endif // !ENGINE_INPUT_BUTTON

