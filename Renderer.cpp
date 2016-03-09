#include "Renderer.h"
#include <iostream>
#include "GameManager.h"

void Renderer::Initialize(int fWidth, int fHeight, const std::string& fTitle)
{
	//SDL Stuff
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
		mIsClosed = true;
		return;
	}
	else
	{
		std::clog << "SDL Initialization Succeeded." << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,	32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	mWindow = SDL_CreateWindow(fTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fWidth, fHeight, SDL_WINDOW_OPENGL);
	mGLContext = SDL_GL_CreateContext(mWindow);

	SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR); 
	SDL_SetCursor(cursor);

	//GLEW Stuff
	GLenum status = glewInit();	//Find openGL supported functions.

	if(status != GLEW_OK)
	{
		std::cerr << "GLEW Failed to Initialize!" << std::endl;
	}
	else
	{
		std::clog << "GLEW Initialization Succeeded." << std::endl;
	}

	PrintGPUSpecs();

	mIsClosed = false;

	//Set OpenGL Blending Mode.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::clog << "Renderer Created Successfully" << std::endl;
}


Renderer::~Renderer()
{
	SDL_GL_DeleteContext(mGLContext);

	SDL_DestroyWindow(mWindow);

	SDL_Quit();

	std::clog << "Renderer Destructed Successfully" << std::endl;
}

void Renderer::Clear(GLfloat fRed, GLfloat fGreen, GLfloat fBlue, GLfloat fAlpha)
{
	glClearColor(fRed, fGreen, fBlue, fAlpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Update()
{
	SDL_GL_SwapWindow(mWindow);

	SDL_Event e;

	//while(SDL_PollEvent(&e))
	//{
	//	if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
	//		mIsClosed = true;
	//}
}

bool Renderer::IsClosed() const
{
	return mIsClosed;
}

void Renderer::PrintGPUSpecs()
{
	printf("\nGraphics Card: %s \n",  glGetString( GL_RENDERER ) );

	const GLubyte* version = glGetString(GL_VERSION);

	printf("OpenGL version Support: %c.%c \n\n", version[0], version[2]);

}

//=======================================================================
// Render List of Game Objects 
//=======================================================================
void Renderer::RenderGameObjects()
{
	auto gameObjects = GameManager::getInstance().GetGameObjects();
	
	for(GameObject* object : gameObjects)
	{
		object->GLRender();
	}
}