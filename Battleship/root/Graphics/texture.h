// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef TEXTURE_BATTLESHIP
#define TEXTURE_BATTLESHIP

#include "../lib.h"

class Texture {

public:

	Texture();
	Texture(int _id);
	Texture(std::string path);
	~Texture();

	int GetID() const;
	int GetWidth() const;
	int GetHeight() const;

private:

	bool GetTextureParams();

	int id;
	int textureWidth;
	int textureHeight;
};

#endif // !TEXTURE_BATTLESHIP
