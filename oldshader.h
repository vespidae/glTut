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
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            //Ensure ifstream objects can throw exceptions
            vShaderFile.exceptions ( std::ifstream::badbit );
            fShaderFile.exceptions ( std::ifstream::badbit );

            try
            {
                //Open files
                vShaderFile.open( vertexPath );
                fShaderFile.open( fragmentPath );
                std::stringstream vShaderStream, fShaderStream;

                //Read files' buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                //Convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();

                //Close file handlers
                vShaderFile.close();
                fShaderFile.close();
            }
            catch ( std::ifstream::failure e )
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
            }

            const GLchar* vShaderSource = vertexCode.c_str();
            const GLchar* fShaderSource = fragmentCode.c_str();

            //Test Code contents
            std::cout << "Vertex Code:\n" << vShaderSource << std::endl;
            std::cout << "Fragment Code:\n" << fShaderSource << std::endl;

            //Compile Shaders
            GLuint vertex, fragment;
            GLint success;
            GLchar infoLog[512];

            //Vertex Shader
            vertex = glCreateShader( GL_VERTEX_SHADER );
            glShaderSource( vertex, 1, &vShaderSource, NULL );
            glCompileShader( vertex );

            //Print compile errors if any
            glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
            if ( !success )
            {
                glGetShaderInfoLog( vertex, 512, NULL, infoLog );
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            //Fragment Shader
            fragment = glCreateShader( GL_FRAGMENT_SHADER );
            glShaderSource( fragment, 1, &fShaderSource, NULL );
            glCompileShader( fragment );

            //Print compile errors if any
            glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
            if( !success )
            {
                glGetShaderInfoLog( fragment, 512, NULL, infoLog );
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            //Shader Program
            this->Program = glCreateProgram();
            glAttachShader( this->Program, vertex );
            glAttachShader( this->Program, fragment );
            glLinkProgram( this->Program );

            //Print linking errors if any
            glGetProgramiv( this->Program, GL_LINK_STATUS, &success );
            if ( !success )
            {
                glGetProgramInfoLog( this->Program, 512, NULL, infoLog );
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            }

            //Delete shaders as they are linked into program now and no longer necessary
            glDeleteShader( vertex );
            glDeleteShader( fragment );
        }

        //Use the current shader
        void Use()
        {
            glUseProgram( this->Program );
        }
};

#endif
