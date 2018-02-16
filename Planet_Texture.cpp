#include "Planet_Texture.h"



Planet_Texture::Planet_Texture(const char* bildName)
{
	Texture = loadBMP_custom(bildName);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
}


Planet_Texture::~Planet_Texture()
{
	glDeleteTextures(1, &Texture);
}
