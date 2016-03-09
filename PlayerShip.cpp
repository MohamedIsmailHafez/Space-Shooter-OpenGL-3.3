#include "PlayerShip.h"


PlayerShip::PlayerShip()
	: Ship(glm::vec2(1280/2, 720/2), glm::vec2(), 0.0f, GameObjectType::PLAYER_SHIP)
{
	mTexture = std::unique_ptr<Texture>(new Texture("./resources/textures/Ship.bmp"));
}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::GLRender()
{
	GameObject::GLRender();

//	if(mIsDying)
//	{
//		GameTextureManager::getInstance().DrawTextured(0, 0, 256, 256, GameTextureManager::getInstance().explosionTex);
//	}
//	else
//	{
//#if DEBUG
//		glColor3f(0,1,0);
//		RenderDebugShip(mPosition.x, mPosition.y);
//#else	
//		GameTextureManager::getInstance().DrawTextured(0, 0, 64, 64, GameTextureManager::getInstance().Player_Ship_Texture);
//#endif
//	}
}

void PlayerShip::Update(float fDeltaTime)
{
	if(mIsDying)
		mTimer -= 1.0f;
}

void PlayerShip::UpdateOrientation(SDL_MouseMotionEvent* motion)
{
	int x = motion->x;
	int y = 720 - motion->y;
	
	glm::vec2 dirVector = glm::vec2(x,y) - glm::vec2(1280.0f/2.0f, 720.0f/2.0f);
	
	float dirVectorMag = sqrtf((dirVector.x * dirVector.x) + (dirVector.y * dirVector.y));
	
	//mNormalizedDir = dirVector/dirVectorMag;
	
	glm::vec2 shipUp(0,1);
	
	float dotProduct = (dirVector.x * shipUp.x) + (dirVector.y * shipUp.y);
	
	float cosAngle = dotProduct / (  glm::length(shipUp) * glm::length(dirVector)) ;
	
	float angle = acos(cosAngle) * 180.f / 3.14f;
	
	SetDirectionAngle( x > 1280.f/2.f ? angle : -angle);
}

void PlayerShip::SetDirectionAngle(float fDirectionAngle)
{
	if( abs(fDirectionAngle - mDirectionangle) < 0.001f)
		return;

	mDirectionangle = fDirectionAngle;
}

void PlayerShip::Fire(glm::vec2 fDirection)
{
	//Bullet* bullet = new Bullet(glm::vec2(GameConfig::getInstance().ScreenWidth/2, GameConfig::getInstance().ScreenHeight/2), fDirection);
	//GameManager::getInstance().Add(bullet);
}
