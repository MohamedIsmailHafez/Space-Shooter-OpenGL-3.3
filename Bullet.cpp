#include "Bullet.h"

Bullet::Bullet(const glm::vec2& fPosition, const glm::vec2& fDirection)
	: GameObject(fPosition, fDirection, 0, GameObjectType::BULLET)
{
	mTexture = std::unique_ptr<Texture>(new Texture("./resources/textures/Bullet.bmp"));
}

Bullet::~Bullet()
{

}

void Bullet::GLRender()
{
	GameObject::GLRender();
}

void Bullet::Update(int fDeltaTime)
{
	mPosition += mDirection * 200.f * (float)fDeltaTime/1000.f;
}
