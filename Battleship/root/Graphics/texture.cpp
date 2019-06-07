// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "texture.h"

Texture::Texture() {
	
	id = -1;
	textureWidth = 0;
	textureHeight = 0;
}

Texture::Texture(int _id) : Texture() {
	
	id = _id;

	if (!GetTextureParams()) {
		Misc::Logger("000t", "Error: Failed to get Texture parameters [GetTextureParams() = false].");
	}
	else {
		Misc::Logger("001t", "Successfully acquired Texture parameters [GetTextureParams() = true].");
	}
}

Texture::Texture(std::string path) : Texture() {

	id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);

	if (!GetTextureParams()) {

		std::stringstream stream;
		stream << "Error: Failed to load asset from[" << path << "] ___[GetTextureParams() = false].";
		Misc::Logger("002t", stream.str());
	}
	else {

		std::stringstream stream;
		stream << "Successfully loaded asset from [" << path << "] ___ [GetTextureParams() = true].";
		Misc::Logger("003t", stream.str());
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
