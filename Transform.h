#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

	glm::vec3& GetPosition() { return mPosition; }
	void SetPosition(const glm::vec3& val) { mPosition = val; }

	glm::vec3& GetRotation() { return mRotation; }
	void SetRotation(const glm::vec3& val) { mRotation = val; }

	glm::vec3& GetScale() { return mScale; }
	void SetScale(const glm::vec3& val) { mScale = val; }

	glm::mat4 GetModelMatrix() const {

		glm::mat4 translate = glm::translate(mPosition);

		glm::vec3 radianRotation = glm::radians(mRotation);
		glm::quat quaternion	 = glm::quat(radianRotation);
		glm::mat4 rotation		 = glm::toMat4(quaternion);

		glm::mat4 scale	= glm::scale(mScale);

		return (translate * rotation * scale);
	}

private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
};


#endif // !TRANSFORM_H



