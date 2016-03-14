#include "Bullet.h"

Texture* Bullet::GetBulletTexture()
{
	static Texture* texture(new Texture("./resources/textures/Bullet.bmp"));
	return texture;
}

Bullet::Bullet(const glm::vec2& fPosition, const glm::vec2& fDirection)
	: GameObject(fPosition, fDirection, 0, GameObjectType::BULLET)
{
}

Bullet::~Bullet()
{

}

void Bullet::GLRender()
{
	mTransform.SetScale(glm::vec3(GetBulletTexture()->GetTextureWidth(), GetBulletTexture()->GetTextureHeight(), 0));

	GetBulletTexture()->Bind(0);

	GameObject::GLRender();
}

void Bullet::Update(int fDeltaTime)
{
	mPosition += mDirection * 2000.f * (float)fDeltaTime/1000.f;
}
