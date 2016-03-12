#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "Ship.h"
#include "Texture.h"
#include "Mesh.h"
#include <memory>
#include "SDL2\SDL_events.h"

class Bullet;

class PlayerShip : public Ship
{
public:
	PlayerShip();
	virtual ~PlayerShip();

	void SetDirectionAngle(float fDirectionAngle);
	GameObject* Fire();

	virtual void GLRender() override;

	void UpdateOrientation(SDL_MouseMotionEvent* motion);

protected:
	virtual void Update(int fDeltaTime) override;

private:
	glm::vec2 mNormalizedDir;
};
#endif
