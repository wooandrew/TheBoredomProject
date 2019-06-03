// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "texture.h"

Texture::Texture() {
	id = -1;
	textureWidth = 0;
	textureHeight = 0;
}
Texture::~Texture() {}

Texture::Texture(int _id) {

	textureWidth = 0;
	textureHeight = 0;

	id = _id;

	if (!GetTextureParams()) {
		std::cerr << Misc::GetDateTime() << " |000t| Error: Failed to get Texture Parameters [GetTextureParams() = false]." << std::endl;
	}
	else {
		std::cerr << Misc::GetDateTime() << " |001t| Successfully acquired Texture Parameters [GetTextureParams() = true]." << std::endl;
	}
}

Texture::Texture(std::string path) {

	textureWidth = 0;
	textureHeight = 0;

	id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);

	if (!GetTextureParams()) {
		std::cerr << Misc::GetDateTime() << " |002t| Error: Failed to get Texture Parameters [GetTextureParams() = false]." << std::endl;
	}
	else {
		std::cerr << Misc::GetDateTime() << " |003t| Successfully acquired Texture Parameters [GetTextureParams() = true]." << std::endl;
	}
}

bool Texture::GetTextureParams() {

	if (id > 0) {

		int mipLevel = 0;
		glBindTexture(GL_TEXTURE_2D, id);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &textureWidth);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &textureHeight);

		return true;
	}

	return false;
}

int Texture::GetID() const { return id; }
int Texture::GetWidth() const { return textureWidth; }
int Texture::GetHeight() const { return textureHeight; }
