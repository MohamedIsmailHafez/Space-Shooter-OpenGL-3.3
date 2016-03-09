#include "Ship.h"

Ship::Ship(const glm::vec2& fPosition, const glm::vec2& fDirection, float fDirectionAngle, GameObjectType fType)
	: GameObject(fPosition, fDirection, fDirectionAngle, fType),
	mIsDying(false),
	mTimer(1.0f)
{

}

Ship::~Ship()
{

}

//=======================================================================
// Debug Ship Function
//=======================================================================
void Ship::RenderDebugShip(float fPosX, float fPosY)
{
	//float size = 20.f;
	//glTranslatef(-fPosX, -fPosY, 0);

	//glBegin(GL_LINE_LOOP);
	//glVertex2f(fPosX, fPosY + 2.0f*size);
	//glVertex2f(fPosX + size, fPosY - size);
	//glVertex2f(fPosX - size, fPosY - size);
	//glEnd();
}


