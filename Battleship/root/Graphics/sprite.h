// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef GRAPHICS_SPRITE
#define GRAPHICS_SPRITE

#include "../lib.h"
#include "texture.h"

class Sprite {

public:

	Sprite();
	Sprite(std::string path);
	Sprite(std::string path, glm::vec3 _position);
	Sprite(std::string path, glm::vec3 _position, float _scale);
	Sprite(std::string path, glm::vec3 _position, glm::vec3 _scale);
	
	void Flip(bool _flip = false);

	void Update() const;
	void Render() const;

	void SetPosition(glm::vec3 _position);

	void RotateTo(float _rotation);

	void SetScale(float _scale);
	void SetScale(glm::vec3 _scale);

	float* GetRotation();
	glm::vec3* GetPosition();
	glm::vec3* GetScale();
	glm::vec3* GetSize();

private:

	Texture texture;

	float rotation;

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 size;

	bool flip;
};

typedef Sprite Image;

#endif // !GRAPHICS_SPRITE
