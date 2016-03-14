#include "EnemyShip.h"
#include "Renderer.h"

const float EnemyShip::SPEED = 200;

Texture* EnemyShip::GetEnemyTexture()
{
	static Texture* texture(new Texture("./resources/textures/EnemyShip.bmp"));
	return texture;
}

EnemyShip::EnemyShip(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, int fLevel)
	: Ship(fPosition, fDirection, fDirectionAngle, GameObjectType::ENEMY_SHIP), mLevel(fLevel)
{
	glm::vec2 dirVector = glm::vec2(Renderer::getInstance().GetWidth()/2.0f, Renderer::getInstance().GetHeight()/2.0f) - mPosition;

	dirVector = glm::normalize(dirVector);

	float dotProduct = (dirVector.x * 0) + (dirVector.y * -1);

	float cosAngle = dotProduct / (1 * glm::length(dirVector) );

	float angle = acos(cosAngle) * 180.f / 3.14f;

	mDirectionangle = (mPosition.x < Renderer::getInstance().GetWidth()/2.f) ? angle : -angle;

	mDirection = dirVector;
}

EnemyShip::~EnemyShip(void)
{
}

void EnemyShip::GLRender()
{
	mTransform.SetScale(glm::vec3(GetEnemyTexture()->GetTextureWidth(), GetEnemyTexture()->GetTextureHeight(), 0));

	GetEnemyTexture()->Bind(0);

	GameObject::GLRender();
}

void EnemyShip::Update(int fDeltaTime)
{
	mPosition += mDirection * SPEED * (float)fDeltaTime/1000.f;

	if(mIsDying)
		mTimer -= 7.5f * (float)fDeltaTime/1000.f;
}