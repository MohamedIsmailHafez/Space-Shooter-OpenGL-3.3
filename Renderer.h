#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>
#include "Mesh.h"
#include "Shader.h"
#include "GameManager.h"


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
	void SwapBuffers() const;

	bool IsClosed() const;
	void SetClosed(bool fValue);

	void RenderGame(GameState fGameState);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	Shader* getShader() {return &mShader;}

private:
	Renderer(){}
	Renderer(const Renderer& other) {}
	void operator=(const Renderer& other) {}

	void PrintGPUSpecs();
	void RenderGameObjects();
	void RenderScore();
	void RenderGameOverScreen();

	SDL_Window*		mWindow;
	SDL_GLContext	mGLContext;
	bool			mIsClosed;
	int				mWidth;
	int				mHeight;
	std::unique_ptr<Mesh> mMesh;
	Shader	mShader;
	Uint32 mLastFrameTime;
};

#endif // RENDERER_H

