// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef GRAPHICS_TEXTURE
#define GRAPHICS_TEXTURE

#include "../lib.h"

class Texture {

public:

	Texture();
	Texture(int _id);
	Texture(std::string path);

	int GetID() const;
	int GetWidth() const;
	int GetHeight() const;

private:

	bool GetTextureParams();

	int id;
	int textureWidth;
	int textureHeight;
};

#endif // !GRAPHICS_TEXTURE
