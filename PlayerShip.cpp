#include "PlayerShip.h"
#include "Bullet.h"
#include "Renderer.h"

Texture* PlayerShip::GetPlayerTexture()
{
	static Texture* texture(new Texture("./resources/textures/PlayerShip.bmp"));
	return texture;
}

PlayerShip::PlayerShip()
	: Ship(glm::vec2(Renderer::getInstance().GetWidth()/2.0f, Renderer::getInstance().GetHeight()/2.0f), glm::vec2(), 0.0f, GameObjectType::PLAYER_SHIP)
{
}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::GLRender()
{
	mTransform.SetScale(glm::vec3(GetPlayerTexture()->GetTextureWidth(), GetPlayerTexture()->GetTextureHeight(), 0));

	GetPlayerTexture()->Bind(0);

	GameObject::GLRender();
}

void PlayerShip::Update(int fDeltaTime)
{
	if(mIsDying)
		mTimer -= 1.0f;
}

void PlayerShip::UpdateOrientation(SDL_MouseMotionEvent* motion)
{
	int x = motion->x;
	int y = motion->y;
	
	glm::vec2 dirVector = glm::vec2(x,y) - glm::vec2(Renderer::getInstance().GetWidth()/2.0f, Renderer::getInstance().GetHeight()/2.0f);
	
	float dirVectorMag = sqrtf((dirVector.x * dirVector.x) + (dirVector.y * dirVector.y));
	
	mNormalizedDir = dirVector/dirVectorMag;
	
	glm::vec2 shipUp(0,-1);
	
	float dotProduct = (dirVector.x * shipUp.x) + (dirVector.y * shipUp.y);
	
	float cosAngle = dotProduct / (  glm::length(shipUp) * glm::length(dirVector)) ;
	
	float angle = acos(cosAngle) * 180.f / 3.14f;
	
	SetDirectionAngle( x > Renderer::getInstance().GetWidth()/2.f ? angle : -angle);
}

void PlayerShip::SetDirectionAngle(float fDirectionAngle)
{
	if( abs(fDirectionAngle - mDirectionangle) < 0.001f)
		return;

	mDirectionangle = fDirectionAngle;
}

GameObject* PlayerShip::Fire()
{
	return (new Bullet(glm::vec2(Renderer::getInstance().GetWidth()/2, Renderer::getInstance().GetHeight()/2), mNormalizedDir));
}
