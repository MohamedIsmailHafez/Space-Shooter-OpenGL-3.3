#include "PlayerShip.h"
#include <vector>

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
public:

	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}

	void Initialize(PlayerShip* ship);
	void HandleEvents();
	void Add(GameObject* fObject);
	void SpawnEnemy();

	const std::vector<GameObject*>& GetGameObjects() const {return GameObjects;}
	//static Uint32 SpawnEnemy(Uint32 interval, void* param);
	//Uint32 callbackSpawnEnemies( Uint32 interval, void* param );

private:
	GameManager();
	virtual ~GameManager();
	GameManager(GameManager const&);
	void operator=(GameManager const&);


	glm::vec2 GetRandomPosOffScreen();

	PlayerShip* mPlayerShip;
	std::vector<GameObject*> GameObjects;
};
#endif  //!GAMEMANAGER_H
