#include "GameManager.h"
#include "SDL2\SDL_events.h"
#include "SDL2\SDL_timer.h"
#include "EnemyShip.h"


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	for (std::vector< GameObject* >::iterator it = GameObjects.begin() ; it != GameObjects.end(); ++it)
	{
		delete (*it);
	} 
	GameObjects.clear();
}

Uint32 callbackSpawnEnemies(Uint32 interval, void* param)
{
	SDL_Event event;
    //SDL_UserEvent userevent;

    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */

    //userevent.type = SDL_USEREVENT;
    //userevent.code = 0;
    //userevent.data1 = &GameManager::SpawnEnemy;
    //userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    //event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
	
	//GameManager::getInstance().SpawnEnemy();

	//SDL_TimerID timerID = SDL_AddTimer( 3 * 1000, callbackSpawnEnemies, "3 seconds waited!" );
	//return 0;
}

void GameManager::Initialize(PlayerShip* ship)
{
	if(ship == nullptr)
		return;

	mPlayerShip = ship;

	SDL_TimerID timerID = SDL_AddTimer( 3 * 1000, callbackSpawnEnemies, "3 seconds waited!" );
}

void GameManager::HandleEvents()
{
	SDL_Event e;

	while( SDL_PollEvent( &e ) )
	{
		if(e.type == SDL_MOUSEMOTION)
		{
			mPlayerShip->UpdateOrientation(&e.motion);
		}
		else if(e.type == SDL_USEREVENT)
		{
			SpawnEnemy();
			//int i;
			///void (*p) (void*) = e.user.data1;
			//p(e.user.data2);
		}
	}
}

void GameManager::Add(GameObject* fObject)
{
	GameObjects.push_back(fObject);
}

void GameManager::SpawnEnemy()
{
	glm::vec2 startlocation = GetRandomPosOffScreen();
	
	int level;
	(((int)startlocation.x + (int)startlocation.y) % 2) == 0 ? level = 0 : level = 1;
	
	EnemyShip* enemy = new EnemyShip(glm::vec2(startlocation.x, startlocation.y), glm::vec2(), 0.f, 0);
	
	GameObjects.push_back(enemy);

	//float Difficulty = 1.f;
	//return 0;
}

glm::vec2 GameManager::GetRandomPosOffScreen()
{
	int side = (rand() % 4) + 1;

	int EnemySize = -10;

	float ScreenWidth = 1280.f/3.0f;
	float ScreenHeight = 720.f/3.0f;

	switch(side)
	{
	case 1:
		return glm::vec2(rand() % (int)ScreenWidth, -EnemySize);
		break;
	case 2:
		return glm::vec2(rand() % (int)ScreenWidth, ScreenHeight + EnemySize);
		break;
	case 3:
		return glm::vec2(-EnemySize, rand() % (int)ScreenHeight);
		break;
	case 4:
		return glm::vec2(ScreenWidth + EnemySize, rand() % (int)ScreenHeight);
		break;
	default:
		return glm::vec2(0,0);
	}
}