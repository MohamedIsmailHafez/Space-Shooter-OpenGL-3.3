#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int numComponents;

	unsigned char* imageData = stbi_load(fileName.c_str(), &mTextureWidth, &mTextureHeight, &numComponents, 4);

	if(imageData == nullptr)
		std::cerr << "\nError: Texture loading failed for texture " << fileName << std::endl;

	glGenTextures(1, &mTexture);	//ask the GPU for a texture buffer.

	glBindTexture(GL_TEXTURE_2D, mTexture);

	//Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);	//free data after passing it to GPU.
}


Texture::~Texture()
{
	glDeleteTextures(1, &mTexture);
}

void Texture::Bind(unsigned int fUnit)
{
	assert(fUnit >= 0 && fUnit <= 31);

	glActiveTexture(GL_TEXTURE0 + fUnit); //Activate a specific texture unit on the GPU. 

	glBindTexture(GL_TEXTURE_2D, mTexture);
}