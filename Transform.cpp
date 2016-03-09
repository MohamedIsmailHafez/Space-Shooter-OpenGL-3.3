#include "Transform.h"


Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) :
	mPosition(pos),
	mRotation(rot),
	mScale(scale) {}
