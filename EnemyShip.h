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
	virtual void Update(int fDeltaTime) override;

private:
	int mLevel;

	static const float SPEED;
};
#endif //!ENEMYSHIP_H
