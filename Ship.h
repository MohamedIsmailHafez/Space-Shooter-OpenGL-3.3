#ifndef SHIP_H
#define SHIP_H

#include "GameObject.h"

class Ship : public GameObject
{
public:
	Ship(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, GameObjectType fType);
	virtual ~Ship();

	bool IsDying() const { return mIsDying; }
	void SetDying(bool val) { mIsDying = val; }

	float GetTimer() const { return mTimer; }

protected:
	virtual void GLRender() override = 0;
	virtual void Update(float fDeltaTime) override = 0;

	void RenderDebugShip(float fPosX, float fPosY);

	float	mTimer;
	bool	mIsDying;
};
#endif //!SHIP_H