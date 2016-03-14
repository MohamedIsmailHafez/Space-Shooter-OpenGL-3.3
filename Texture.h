#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "gl/glew.h"

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int fUnit);

	virtual ~Texture();

	int GetTextureWidth()  const { return mTextureWidth;  }
	int GetTextureHeight() const { return mTextureHeight; }

private:
	int mTextureWidth;
	int mTextureHeight;

	GLuint mTexture; //OpenGL Texture Handle.
};
#endif	//!TEXTURE_H
