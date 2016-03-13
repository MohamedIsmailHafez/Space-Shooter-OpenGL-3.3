#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "Shader.h"
#include "Texture.h"

class TextRenderer
{
public:

	static TextRenderer& getInstance()
	{
		static TextRenderer instance;
		return instance;
	}

	void Print(const char * text, int x, int y, int size);

private:
	TextRenderer();
	virtual ~TextRenderer();

	Shader mShader;
	Texture* mFontTexture;
};
#endif
