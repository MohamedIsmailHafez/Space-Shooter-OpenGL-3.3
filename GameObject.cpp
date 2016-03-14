#include "GameObject.h"
#include "Shader.h"
#include "Renderer.h"
#include "EnemyShip.h"

Texture* GameObject::GetExplosionTexture()
{
	static Texture* texture(new Texture("./resources/textures/Explosion.bmp"));
	return texture;
}

GameObject::GameObject(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, GameObjectType fType)
	: mPosition(fPosition), mDirection(fDirection), mDirectionangle(fDirectionAngle), mType(fType), mTexture(nullptr)
{

}

GameObject::~GameObject()
{

}

void GameObject::GLRender()
{
	glm::mat4 projection = glm::ortho(0.0f, (float)Renderer::getInstance().GetWidth(), (float)Renderer::getInstance().GetHeight(), 0.0f);

	mTransform.SetPosition(glm::vec3(GetPosition(), 0.0f));

	mTransform.SetRotation(glm::vec3(0,0,mDirectionangle));

	glm::mat4 ModelProjection = projection * mTransform.GetModelMatrix();

	Renderer::getInstance().getShader()->Update(ModelProjection);

	auto enemyShip = dynamic_cast<EnemyShip*>(this);

	if(enemyShip && enemyShip->IsDying())
		GetExplosionTexture()->Bind(0);
}
