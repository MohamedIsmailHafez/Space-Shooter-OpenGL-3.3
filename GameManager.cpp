#include "GameManager.h"
#include "SDL2\SDL_events.h"
#include "EnemyShip.h"
#include <time.h>
#include "Renderer.h"


GameManager::GameManager() : mGameState(GameState::GAMEPLAY)
{
}

GameManager::~GameManager()
{
	for (std::vector< GameObject* >::iterator it = GameObjects.begin(); it != GameObjects.end(); ++it)
	{
		delete (*it);
	} 
	GameObjects.clear();
}

Uint32 callbackSpawnEnemies(Uint32 fInterval, void* fParam)
{
	SDL_Event event;

    event.type = SDL_USEREVENT;

    SDL_PushEvent(&event);
    return(fInterval);
}

void GameManager::Initialize(PlayerShip* fShip)
{
	if(fShip == nullptr)
		return;

	mPlayerShip = fShip;

	GameObjects.push_back(mPlayerShip);

	srand((unsigned int)time(NULL));

	mTimerID = SDL_AddTimer( 1 * 1000, callbackSpawnEnemies, "3 seconds waited!" );
}

void GameManager::HandleEvents()
{
	SDL_Event e;

	while( SDL_PollEvent( &e ) )
	{
		switch (e.type)
		{
		case SDL_MOUSEMOTION:
			mPlayerShip->UpdateOrientation(&e.motion);
			break;
		case SDL_USEREVENT:
			SpawnEnemy();
			break;
		case SDL_MOUSEBUTTONDOWN:
			GameObjects.push_back( mPlayerShip->Fire() );
			break;
		case SDL_QUIT:
			Renderer::getInstance().SetClosed(true);

		default:
			break;
		}

		if(e.key.keysym.sym == SDLK_ESCAPE)
			Renderer::getInstance().SetClosed(true);
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

	//SDL_RemoveTimer(timerID);
}

glm::vec2 GameManager::GetRandomPosOffScreen()
{
	int side = (rand() % 4) + 1;

	int EnemySize = -10;

	int ScreenWidth  = Renderer::getInstance().GetWidth();
	int ScreenHeight = Renderer::getInstance().GetHeight();

	switch(side)
	{
	case 1:
		return glm::vec2(rand() % ScreenWidth, -EnemySize);
		break;
	case 2:
		return glm::vec2(rand() % ScreenWidth, ScreenHeight + EnemySize);
		break;
	case 3:
		return glm::vec2(-EnemySize, rand() % ScreenHeight);
		break;
	case 4:
		return glm::vec2(ScreenWidth + EnemySize, rand() % ScreenHeight);
		break;
	default:
		return glm::vec2(0,0);
	}
}

void GameManager::UpdateGameObjects()
{
	int currentTime = SDL_GetTicks();
	int timeElapsed = currentTime - previousTime;
	previousTime = currentTime;

	for(auto obj : GameObjects)
	{
		obj->Update(timeElapsed);

		if(obj->GetType() == GameObjectType::BULLET)
		{
			if(OutofBounds(obj->GetPosition()))
			{
				GameObjects.erase(std::find(GameObjects.begin(), GameObjects.end(), obj));
				break;
			}
			else
			{
				for(GameObject* object : GameObjects)
				{
					if(EnemyShip* enemy = dynamic_cast<EnemyShip*>(object))
					{
						if(Distance(enemy->GetPosition(), obj->GetPosition()) < 40)
						{
							GameObjects.erase(std::find(GameObjects.begin(), GameObjects.end(), obj));
							enemy->SetDying(true);
							//UpdateScore();
							return;
						}
			
					}
				}
			}
		}


		if(obj->GetType() == GameObjectType::ENEMY_SHIP)
		{
			if(dynamic_cast<EnemyShip*>(obj)->GetTimer() <= 0)
			{
				GameObjects.erase(std::find(GameObjects.begin(), GameObjects.end(), obj));
				break;
			}

			if(Distance(obj->GetPosition(), mPlayerShip->GetPosition()) < 40)
			{
				PlayerShip *playerShip = dynamic_cast<PlayerShip *>(mPlayerShip);
				if (NULL != playerShip)
				{
					playerShip->SetDying(true);
				}
			}
		}

		if(obj->GetType() == GameObjectType::PLAYER_SHIP)
		{
			if(dynamic_cast<PlayerShip*>(obj)->GetTimer() <= 0)
				mGameState = GameState::GAMEOVER;
		}

	}
}

bool GameManager::OutofBounds(const glm::vec2& fPosition)
{
	return (fPosition.x > Renderer::getInstance().GetWidth() 
			|| fPosition.y > Renderer::getInstance().GetHeight() 
			|| fPosition.x < 0 
			|| fPosition.y < 0);
}

float GameManager::Distance(const glm::vec2& fPosition1, const glm::vec2& fPosition2)
{
	return sqrt( (fPosition2.x - fPosition1.x)*((fPosition2.x - fPosition1.x)) + ((fPosition2.y - fPosition1.y))*((fPosition2.y - fPosition1.y)) );
}