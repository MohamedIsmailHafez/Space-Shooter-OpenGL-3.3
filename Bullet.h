#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"


class Bullet : public GameObject
{
public:
	Bullet(const glm::vec2& fPosition, const glm::vec2& fDirection);
	virtual ~Bullet();

	virtual void GLRender() override;
protected:
	virtual void Update(int fDeltaTime) override;

};
#endif //!BULLET_H
