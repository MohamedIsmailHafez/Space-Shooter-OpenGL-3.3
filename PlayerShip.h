#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "Ship.h"
#include "Texture.h"
#include "Mesh.h"
#include <memory>
#include "SDL2\SDL_events.h"

class PlayerShip : public Ship
{
public:
	PlayerShip();
	virtual ~PlayerShip();

	void SetDirectionAngle(float fDirectionAngle);
	void Fire(glm::vec2 fDirection);

	virtual void GLRender() override;

	void UpdateOrientation(SDL_MouseMotionEvent* motion);

protected:
	virtual void Update(float fDeltaTime) override;
};
#endif
