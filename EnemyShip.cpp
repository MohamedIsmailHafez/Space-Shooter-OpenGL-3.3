#include "EnemyShip.h"


EnemyShip::EnemyShip(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, int fLevel)
	: Ship(fPosition, fDirection, fDirectionAngle, GameObjectType::ENEMY_SHIP), mLevel(fLevel)
{

	mTexture = std::unique_ptr<Texture>(new Texture("./resources/textures/Ship.bmp"));

	glm::vec2 dirVector = glm::vec2(1280.f/2.0f, 720.f/2.0f) - mPosition;

	glm::normalize(dirVector);

	float dotProduct = (dirVector.x * 0) + (dirVector.y * 1);

	float cosAngle = dotProduct / (1 * glm::length(dirVector) );

	float angle = acos(cosAngle) * 180.f / 3.14f;

	mPosition.x < 1280/2.0f ? mDirectionangle = -angle : mDirectionangle = angle;

	mDirection = dirVector;
}

EnemyShip::~EnemyShip(void)
{
}

void EnemyShip::GLRender()
{
	GameObject::GLRender();
}

void EnemyShip::Update(float fDeltaTime)
{

}