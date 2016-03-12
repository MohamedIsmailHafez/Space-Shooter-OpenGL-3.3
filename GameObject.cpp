#include "GameObject.h"
#include "Shader.h"
#include "Renderer.h"

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

	mTransform.SetScale(glm::vec3(mTexture->GetTextureWidth(), mTexture->GetTextureHeight(), 0));

	mTransform.SetPosition(glm::vec3(GetPosition(), 0.0f));

	mTransform.SetRotation(glm::vec3(0,0,mDirectionangle));

	glm::mat4 ModelProjection = projection * mTransform.GetModelMatrix();

	Shader::getInstance().Update(ModelProjection);

	mTexture->Bind(0);
}
