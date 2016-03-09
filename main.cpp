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
	/*Renderer& renderer = Renderer::getInstance();

	renderer.Initialize(800, 600, "OpenGL Window");

	Shader shader("./resources/shaders/basicShader");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0) ),
						  Vertex(glm::vec3( 0.5, -0.5, 0), glm::vec2(1, 0) ),
						  Vertex(glm::vec3( 0.0,  0.5, 0), glm::vec2(0.5, 1) )};

	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
	
	Texture texture("./resources/textures/bricks.jpg");

	Transform transform;

	float counter = 0.0f;

	while(!renderer.IsClosed())
	{
		renderer.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();

		transform.GetRotation().x = counter;

		shader.Update(transform);

		texture.Bind(0);
		
		mesh.Draw();

		renderer.Update();

		counter += 0.01f;
	}*/

	Renderer& renderer = Renderer::getInstance();

	renderer.Initialize(1280, 720, "Space Shooter");

	Shader& shader = Shader::getInstance();

	shader.Load("./resources/shaders/basicShader");

	GameManager& manager = GameManager::getInstance();

	PlayerShip ship;

	manager.Initialize(&ship);


	while(!renderer.IsClosed())
	{
		manager.HandleEvents();

		renderer.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		shader.Bind();

		renderer.RenderGameObjects();
		
		ship.GLRender();

		renderer.Update();
	}

	return 0;
}