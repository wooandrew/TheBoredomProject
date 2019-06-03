// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "sprite.h"

#define VEC3_EMPTY		glm::vec3()
#define VEC3_VALUE1		glm::vec3(1)

Sprite::Sprite() {

	texture = Texture();

	rotation = 0;

	position = VEC3_EMPTY;
	size = VEC3_EMPTY;
	scale = VEC3_VALUE1;

	bFlip = false;
}
Sprite::~Sprite() {}

Sprite::Sprite(std::string path) : Sprite() {

	texture = Texture(path);
	size = glm::vec3(static_cast<float>(texture.GetWidth()), static_cast<float>(texture.GetHeight()), 1);
}

Sprite::Sprite(std::string path, glm::vec3 _position) : Sprite(path) {
	position = _position;
}

Sprite::Sprite(std::string path, glm::vec3 _position, float _scale) : Sprite(path, _position) {
	scale.x = _scale;
	scale.y = _scale;
}

Sprite::Sprite(std::string path, glm::vec3 _position, glm::vec3 _scale) : Sprite(path, _position) {
	scale = _scale;
}

void Sprite::flip(bool _flip) { bFlip = _flip; }

void Sprite::Update() const {}

void Sprite::Render() const {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	glLoadIdentity();

	// TRANSLATE -> ROTATE -> SCALE
	glPushMatrix();

	glTranslatef(position.x, position.y, 0);
	glRotatef(rotation, 0, 0, 1);

	glScalef(scale.x, scale.y, 0);

	// Rendering
	glColor4f(1, 1, 1, 1);

	if (bFlip) {

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);				glVertex2i(texture.GetWidth() / 2, -texture.GetHeight() / 2);
			glTexCoord2f(1, 0);				glVertex2i(-texture.GetWidth() / 2, -texture.GetHeight() / 2);
			glTexCoord2f(1, 1);				glVertex2i(-texture.GetWidth() / 2, texture.GetHeight() / 2);
			glTexCoord2f(0, 1);				glVertex2i(texture.GetWidth() / 2, texture.GetHeight() / 2);
		}
		glEnd();
	}
	else {

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);				glVertex2i(-texture.GetWidth() / 2, -texture.GetHeight() / 2);
			glTexCoord2f(1, 0);				glVertex2i(texture.GetWidth() / 2, -texture.GetHeight() / 2);
			glTexCoord2f(1, 1);				glVertex2i(texture.GetWidth() / 2, texture.GetHeight() / 2);
			glTexCoord2f(0, 1);				glVertex2i(-texture.GetWidth() / 2, texture.GetHeight() / 2);
		}
		glEnd();
	}

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Sprite::SetPosition(glm::vec3 _position) {
	position = _position;
}

void Sprite::SetRotation(float _rotation) {
	rotation = _rotation;
}

void Sprite::SetScale(float _scale) {
	scale.x = _scale;
	scale.y = _scale;
}

void Sprite::SetScale(glm::vec3 _scale) {
	scale = _scale;
}

float* Sprite::GetRotation() { return &rotation; }
glm::vec3* Sprite::GetPosition() { return &position; }
glm::vec3* Sprite::GetScale() { return &scale; }
glm::vec3* Sprite::GetSize() { return &size; }