// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef GRAPHICS_TEXT
#define GRAPHICS_TEXT

#include "../lib.h"

class Text {

public:

	Text();

	void LoadFont(std::string fontPath, int fontSize);

	void RenderText(std::string text, int fontSize);
	void RenderText(std::string text, int fontSize, glm::vec3 _position);
	void RenderText(std::string text, int fontSize, glm::vec3 _position, glm::vec3 color);

	void RenderTextBox(std::string text, glm::vec3 _position, glm::vec3 color);

	void RenderAll(std::string text, int fontSize, glm::vec3 _position, glm::vec3 color);

private:

	int fontSize;
	glm::vec2 StringDimensions;
	std::map<int, struct dtx_font*> font;
};

#endif // !GRAPHICS_TEXT
