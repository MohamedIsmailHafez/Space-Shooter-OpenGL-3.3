#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glm/glm.hpp"
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"
#include <memory>

enum class GameObjectType {PLAYER_SHIP, ENEMY_SHIP, BULLET};

class GameObject
{
public:
	GameObject(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, GameObjectType fType);
	virtual ~GameObject(void);

	virtual void GLRender();
	virtual void Update(int fDeltaTime) = 0;

	glm::vec2 GetPosition() const { return mPosition; }
	GameObjectType GetType() const { return mType; }

protected:
	glm::vec2	mPosition;
	glm::vec2	mDirection;
	float		mDirectionangle;
	GameObjectType mType;

	Transform mTransform;
	std::unique_ptr<Texture> mTexture;
};
#endif //!GAMEOBJECT_H

