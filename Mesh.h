#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"
#include "gl/glew.h"

struct Vertex
{
	Vertex(const glm::fvec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() {return &texCoord;}

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();

	void Draw();

private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,

		NUM_BUFFERS
	};

	GLuint mVertexArrayObject;
	GLuint mVertexArrayBuffers[NUM_BUFFERS];

	unsigned int mDrawCount;
};
#endif // MESH_H
