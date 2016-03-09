#include "GameObject.h"
#include "Shader.h"

GameObject::GameObject(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, GameObjectType fType)
	: mPosition(fPosition), mDirection(fDirection), mDirectionangle(fDirectionAngle), mType(fType), mTexture(nullptr)
{
	Vertex vertices[] = {	Vertex(glm::vec3( -0.5f, -0.5f, 0.0f), glm::vec2(0, 0) ),
							Vertex(glm::vec3(  0.5f, -0.5f, 0.0f), glm::vec2(1, 0) ),
							Vertex(glm::vec3(  0.5f,  0.5f, 0.0f), glm::vec2(1, 1) ),
							Vertex(glm::vec3( -0.5f,  0.5f, 0.0f), glm::vec2(0, 1) )};


	mMesh = std::unique_ptr<Mesh>(new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0])));
}

GameObject::~GameObject()
{

}

void GameObject::GLRender()
{
	glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f);

	mTransform.SetScale(glm::vec3(mTexture->GetTextureWidth(), mTexture->GetTextureHeight(), 0));

	mTransform.SetPosition(glm::vec3(GetPosition(), 0.0f));

	mTransform.SetRotation(glm::vec3(0,0,mDirectionangle));

	glm::mat4 ModelProjection = projection * mTransform.GetModelMatrix();

	Shader::getInstance().Update(ModelProjection);

	mTexture->Bind(0);

	mMesh->Draw();
}
