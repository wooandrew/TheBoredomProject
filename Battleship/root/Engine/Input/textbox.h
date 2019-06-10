// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef ENGINE_INPUT_TEXTBOX
#define ENGINE_INPUT_TEXTBOX

#include "../../lib.h"

#include "../engine.h"
#include "../Math/math.h"
#include "../../Graphics/sprite.h"
#include "../../Graphics/text.h"

#include "mouse.h"
#include "keyboard.h"

class Textbox {

public:

	Textbox(std::string path, glm::vec3 _position, float scale, bool _update = false);
	Textbox(Image& _textboximage, bool _update = false);

	void Update();
	void Render(Text& font, int size = 56, glm::vec3 color = glm::vec3());

	std::string GetText() const;
	void StopUpdate();

private:

	bool update;

	std::vector<char> keyToChar;
	std::string tbText;

	Image tbImage;
	Rect::XYWH rect;
};

#endif // !ENGINE_INPUT_TEXTBOX
