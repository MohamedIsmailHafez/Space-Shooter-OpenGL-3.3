#include "TextRenderer.h"
#include <vector>
#include "glm\detail\func_trigonometric.hpp"
#include "Mesh.h"


TextRenderer::TextRenderer()
{
	mShader.Load("./resources/shaders/Text2DShader");
	mFontTexture = new Texture("./resources/fonts/font.tga");
}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Print(const char * text, int x, int y, int size)
{
	mShader.Bind();

	mFontTexture->Bind(0);
	
	unsigned int length = strlen(text);
	
	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	
	for ( unsigned int i=0 ; i<length ; i++ )
	{
		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );
	
		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
	
		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;
	
		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left);
		UVs.push_back(uv_down_left);
		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
	}
	
	std::vector<Vertex> Vertices;
	
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		Vertex v(vertices[i], UVs[i]);
	
		Vertices.push_back(v);
	}
	
	Mesh m(&Vertices[0], Vertices.size());
	
	m.Draw();
}