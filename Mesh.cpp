#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	mDrawCount = numVertices;

	glGenVertexArrays(1, &mVertexArrayObject);
	glBindVertexArray(mVertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for(unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}


	//Generate Buffers.
	//================================================================================================
	glGenBuffers(NUM_BUFFERS, mVertexArrayBuffers);
	//================================================================================================


	//Vertices
	//================================================================================================
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//================================================================================================

	//Texture Coordinates
	//================================================================================================
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//================================================================================================

	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);

	glDeleteBuffers(1, &mVertexArrayBuffers[POSITION_VB]);
	glDeleteBuffers(1, &mVertexArrayBuffers[TEXCOORD_VB]);
}

void Mesh::Draw()
{
	glBindVertexArray(mVertexArrayObject);

	glDrawArrays(GL_QUADS, 0, mDrawCount);
	
	glBindVertexArray(0);
}
