#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <thread>
//#include "../../lib/display.cpp"
//#include "mesh.h"
//#include "shader.h"
//#include "texture.h"
//#include "transform.h"
//#include "camera.h"

#version 150 //"the following code is GLSL 1.50 code"
in vec2 position; //specify vertex attribute

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char *argv[])
{
    //Initializes video module (includes everything needed to create a window and OpenGL context)
    SDL_Init(SDL_INIT_VIDEO);

    //Tell SDL that you want a forward-compatible OpenGL 3.2 context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    //Create a stencil buffer
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //Create a window(title, x, y, width, height, window properties)
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_OPENGL);

    //Create OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);

    //Query and load OpenGL extensions
    //Force GLEW to use a modern OpenGL method for checking if a function is available
    glewExperimental = GL_TRUE;
    glewInit();

    //Initialize veritces
    float vertices[] = {
        0.0f, 0.5f,     //vertex 1
        0.5f, -0.5f,    //vertex 2
        -0.5f, -0.5f    //vertex 3
    };

    //Generate buffers
    //Generate vertex buffer object
    GLuint vertexBufferObjectTri;
    
    //Memory for the graphics card is managed by OpenGL
    //Instead of pointers, cross-platform substitutes for unsigned integers are used to reference buffers
    glGenBuffers(1, &vertexBufferObjectTri);

    //Make our VBO the the active object to upload data to it
    //specifically the active array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Copy vertex data to active object

    printf("%u\n", vertexBufferObjectTri);

    //Event loop
    SDL_Event windowEvent;
    while (true)
    {
        //Check for any new events that must be handled
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
        }

        //Swap front and back buffer after new thing has been drawn by application
        SDL_GL_SwapWindow(window);
    }

    //Delete OpenGL context, cleaning up the resources
    SDL_GL_DeleteContext(context);

    //Destroy window and graphics surface
    SDL_Quit();

    return 0;
}
