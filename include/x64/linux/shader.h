#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <../../GL/glew.h>

class Shader
{
	public:
		GLuint Program;
		//constructor generates shader on the fly
		Shader( const GLchar* vertexPath, const GLchar* fragmentPath )
		{
			//Retrieve the vertex/fragment source code from file path
		}
}
