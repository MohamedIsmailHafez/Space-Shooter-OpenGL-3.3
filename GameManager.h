#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "PlayerShip.h"
#include <vector>
#include "SDL2\SDL_timer.h"

enum class GameState {GAMEPLAY, GAMEOVER};

class GameManager
{
public:

	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}

	void Initialize(PlayerShip* fShip);
	void HandleEvents();
	void Add(GameObject* fObject);
	void SpawnEnemy();

	const std::vector<GameObject*>& GetGameObjects() const {return GameObjects;}
	void UpdateGameObjects();
	GameState GetGameState() { return mGameState; }

	int GetScore() const;

	
private:
	GameManager();
	virtual ~GameManager();
	GameManager(GameManager const&);
	void operator=(GameManager const&);


	glm::vec2 GetRandomPosOffScreen();
	bool OutofBounds(const glm::vec2& fPosition);

	float Distance(const glm::vec2& fPosition1, const glm::vec2& fPosition2);
	void UpdateScore();
	PlayerShip* mPlayerShip;
	std::vector<GameObject*> GameObjects;
	SDL_TimerID mTimerID;
	int previousTime;
	GameState mGameState;
	int mScore;
};
#endif  //!GAMEMANAGER_H
