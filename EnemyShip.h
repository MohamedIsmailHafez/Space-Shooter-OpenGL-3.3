#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "Ship.h"

class EnemyShip : public Ship
{
public:
	EnemyShip(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, int fLevel);
	virtual ~EnemyShip();

	virtual void GLRender() override;


protected:
	virtual void Update(float fDeltaTime) override;

private:
	int mLevel;
};
#endif //!ENEMYSHIP_H
