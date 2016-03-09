#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>

class Renderer
{
public:

	static Renderer& getInstance()
	{
		static Renderer instance;
		return instance;
	}

	void Initialize(int fWidth, int fHeight, const std::string& fTitle);
	virtual ~Renderer();

	void Clear(GLfloat fRed, GLfloat fGreen, GLfloat fBlue, GLfloat fAlpha);
	void Update();

	bool IsClosed() const;

	void RenderGameObjects();

private:
	Renderer(){}
	Renderer(const Renderer& other) {}
	void operator=(const Renderer& other) {}

	void PrintGPUSpecs();

	SDL_Window*		mWindow;
	SDL_GLContext	mGLContext;
	bool			mIsClosed;
};


#endif // RENDERER_H

