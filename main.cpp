#include <iostream>
#include <GL/glew.h>
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include <memory>
#include "PlayerShip.h"
#include "GameManager.h"
#include "EnemyShip.h"

int main(int argc, char** argv)
{
	Renderer& renderer = Renderer::getInstance();

	renderer.Initialize(1280, 720, "Space Shooter");

	Shader& shader = Shader::getInstance();

	shader.Load("./resources/shaders/basicShader");

	GameManager& manager = GameManager::getInstance();

	manager.Initialize(new PlayerShip);

	while(!renderer.IsClosed())
	{
		manager.HandleEvents();

		manager.UpdateGameObjects();

		renderer.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		shader.Bind();

		renderer.RenderGameObjects(manager.GetGameState());

		renderer.SwapBuffers();
	}

	return 0;
}