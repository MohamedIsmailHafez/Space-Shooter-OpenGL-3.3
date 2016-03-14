#include "Renderer.h"
#include "PlayerShip.h"
#include "GameManager.h"

int main(int argc, char** argv)
{
	Renderer& renderer = Renderer::getInstance();

	renderer.Initialize(1280, 720, "Space Shooter");

	GameManager& manager = GameManager::getInstance();

	manager.Initialize(new PlayerShip);

	while(!renderer.IsClosed())
	{
		manager.HandleEvents();

		manager.UpdateGameObjects();

		renderer.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		renderer.RenderGame(manager.GetGameState());
	}

	return 0;
}