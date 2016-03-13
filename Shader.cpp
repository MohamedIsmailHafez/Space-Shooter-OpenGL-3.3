#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader()
{

}

void Shader::Load(const std::string& fileName)
{
	mProgram = glCreateProgram();	//Create new Shader Program on the GPU.

	mShaders[static_cast<unsigned>(SHADER_TYPE::VERTEX_SHADER)]		= CreateShader(LoadShader(fileName + ".vs"),	GL_VERTEX_SHADER);
	mShaders[static_cast<unsigned>(SHADER_TYPE::FRAGMENT_SHADER)]	= CreateShader(LoadShader(fileName + ".fs"),	GL_FRAGMENT_SHADER);

	//Add all shaders to the shader program.
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(mProgram, mShaders[i]);

	glBindAttribLocation(mProgram, 0, "position");
	glBindAttribLocation(mProgram, 1, "texCoord");

	glLinkProgram(mProgram);
	CheckShaderError(mProgram, GL_LINK_STATUS, true, "Error: Shader Program linking failed: ");

	glValidateProgram(mProgram);
	CheckShaderError(mProgram, GL_VALIDATE_STATUS ,true, "Error: Shader Program is invalid: ");

	mUniforms[TRANSFORM_U] = glGetUniformLocation(mProgram, "transform");
}

void Shader::Bind()
{
	glUseProgram(mProgram);
}

//void Shader::Update(const Transform& trans)
void Shader::Update(const glm::mat4& trans)
{
	//glm::mat4 transform = trans.GetModelMatrix();

	glUniformMatrix4fv(mUniforms[TRANSFORM_U], 1, GL_FALSE, &(trans[0][0]));
}

Shader::~Shader()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(mProgram, mShaders[i]);
		glDeleteShader(mShaders[i]);
	}

	glDeleteProgram(mProgram);
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::CreateShader(const std::string& source, unsigned int shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if(shader == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	const GLchar* shadersource[1];
	GLint shaderSourceLength[1];

	shadersource[0]			= source.c_str();
	shaderSourceLength[0]	= source.length();

	glShaderSource(shader, 1, shadersource, shaderSourceLength);
	
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}