// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "text.h"

Text::Text() {
	fontSize = 0;
	StringDimensions = glm::vec2();
}

void Text::LoadFont(std::string fontPath, int fontSize) {

	std::string realPath = fontPath;
	const char* c_fontPath = realPath.c_str();

	struct dtx_font* fontStruct;
	if (!(fontStruct = dtx_open_font(c_fontPath, fontSize))) {

		std::stringstream stream;
		stream << "Error: Failed to load font from [" << fontPath << "].";
		Misc::Logger("000f", stream.str());
	}
	else {
		font.insert(std::pair<int, struct dtx_font*>(fontSize, fontStruct));

		std::stringstream stream;
		stream << "Successfully loaded font from [" << fontPath << "].";
		Misc::Logger("001f", stream.str());
	}
}

void Text::RenderText(std::string text, int fontSize) {

	if (font.find(fontSize) != font.end()) {

		dtx_use_font(font.find(fontSize)->second, fontSize);

		glPushMatrix();

		glColor4f(0, 0, 0, 1);
		dtx_string(text.c_str());

		glPopMatrix();
	}
}

void Text::RenderText(std::string text, int fontSize, glm::vec3 _position) {

	if (font.find(fontSize) != font.end()) {

		dtx_use_font(font.find(fontSize)->second, fontSize);

		glPushMatrix();

		glTranslatef(_position.x, _position.y, 0);
		glColor4f(0, 0, 0, 1);
		dtx_string(text.c_str());

		glPopMatrix();
	}
}

void Text::RenderText(std::string text, int fontSize, glm::vec3 _position, glm::vec3 color) {

	if (font.find(fontSize) != font.end()) {

		dtx_use_font(font.find(fontSize)->second, fontSize);

		glPushMatrix();

		glTranslatef(_position.x, _position.y, 0);
		glColor4f(color.x, color.y, color.z, 1);
		dtx_string(text.c_str());

		glPopMatrix();
	}
}

// Debugging
void Text::RenderTextBox(std::string text, glm::vec3 _position, glm::vec3 color) {

	float width = dtx_string_width(text.c_str());
	float height = dtx_string_height(text.c_str());

	float x = _position.x;
	float y = _position.y;

	glLoadIdentity();

	// TRANSLATE -> ROTATE -> SCALE
	glPushMatrix();

	// Rendering
	glColor4f(color.x, color.y, color.z, 1);
	glBegin(GL_LINES);
	{
		glVertex2f(x, y);
		glVertex2f(x + width, y);

		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);

		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);

		glVertex2f(x, y + height);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}

void Text::RenderAll(std::string text, int fontSize, glm::vec3 _position, glm::vec3 color) {

	if (font.find(fontSize) != font.end()) {

		dtx_use_font(font.find(fontSize)->second, fontSize);

		glPushMatrix();

		glTranslatef(_position.x, _position.y, 0);
		glColor4f(color.x, color.y, color.z, 1);
		dtx_string(text.c_str());

		glPopMatrix();
	}

	float width = dtx_string_width(text.c_str());
	float height = dtx_string_height(text.c_str());

	float x = _position.x;
	float y = _position.y;

	glLoadIdentity();

	// TRANSLATE -> ROTATE -> SCALE
	glPushMatrix();

	// Rendering
	glColor4f(color.x, color.y, color.z, 1);
	glBegin(GL_LINES);
	{
		glVertex2f(x, y);
		glVertex2f(x + width, y);

		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);

		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);

		glVertex2f(x, y + height);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}
