#define GLEW_STATIC

#include <iostream>
#include <thread>

#include "../../../include/GL/glew.h"
#include "../../../include/SDL2/SDL.h"
#include "../../../include/SDL2/SDL_opengl.h"
#include "../../../include/x64/linux/shader.h"
#include "../../../lib/x64/linux/display.cpp"

//#include "mesh.h"
//#include "shader.h"
//#include "texture.h"
//#include "transform.h"
//#include "camera.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char *argv[])
{
    //Initializes video module (includes everything needed to create a window and OpenGL context)
    SDL_Init(SDL_INIT_EVERYTHING);

    //Tell SDL that you want a forward-compatible, OpenGL 3.3 context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //Create a stencil buffer
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //Create a window(title, x, y, width, height, window properties)
    SDL_Window* window = SDL_CreateWindow("OpenGL", 600, 100, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_OPENGL);

    //Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    //Query and load OpenGL extensions
    //Force GLEW to use a modern OpenGL method for checking if a function is available
    glewExperimental = GL_TRUE;

    //Initialize GLEW and confirm it's functioning okay
    if (GLEW_OK != glewInit())
    {
	std::cout << "Failed to initialize GLEW" << std::endl;

	return EXIT_FAILURE;
    }

    //Define our viewport
    glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    //Create full shader program based on shader header file definition
    Shader shaTri( "../../../include/x64/linux/core.vs", "../../../include/x64/linux/core.fs" );
    
    //Create vertex data
    //Initialize veritces
    //float X, float Y, float Z, float R, float G, float B
    GLfloat glVerticesTri[] = {
         0.0f,  0.5f,  0.0f,    0.0f, 0.0f, 1.0f,  //middle top
         0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 0.0f,  //bottom right
        -0.5f, -0.5f,  0.0f,    1.0f, 0.0f, 0.0f   //bottom left
    };

    //Generate vertex buffer object and vertex array object
    GLuint vtxBufObjTri, vtxArrObjTri;

    //Memory for the graphics card is managed by OpenGL
    //Instead of pointers, cross-platform substitutes for unsigned integers are used to reference buffers
    glGenBuffers( 1, &vtxBufObjTri );
    glGenVertexArrays( 1, &vtxArrObjTri );

    //Bind vertex array
    glBindVertexArray( vtxArrObjTri );

    //Make our VBO the active object to upload data to it
    //specifically the active array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vtxBufObjTri);
    glBufferData( GL_ARRAY_BUFFER, sizeof( glVerticesTri ), glVerticesTri, GL_STATIC_DRAW );

    //Create vertex pointer
    //point to start, number of sets of vertices, data type, ???, ???, ???
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE , 6 * sizeof( GLfloat ), ( GLvoid * ) 0 );

    //Enable vertex array
    glEnableVertexAttribArray( 0 );

    //Create vertex pointer
    //point to start, number of sets of vertices, data type, ???, ???, ???
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE , 6 * sizeof( GLfloat ), ( GLvoid * ) ( 3 * sizeof( GLfloat ) ) );

    //Enable vertex array
    glEnableVertexAttribArray( 1 );

    //Unbind vertex buffer/array
    // commented out the following: glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    //Copy vertex data to active object
    //printf("%u\n", vtxBufObjTri);

    //Create event loop
    SDL_Event windowEvent;
    while (true)
    {
        //Check for any new events that must be handled
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) 
	    {
		break;
	    }
        }

	//Update app logic
	//foo

	//Clear whatever is onscreen with designated clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw via OpenGL
	//Use created shader program and bind vertex array object
	//commented out the following: glUseProgram( shaderProgram );
        shaTri.Use();
	glBindVertexArray( vtxArrObjTri );

	//Actually draw object 
	//depending on draw mode, starting vertex, and number of vertices
	glDrawArrays( GL_TRIANGLES, 0, 3 );

	//Unbind vertex array
	glBindVertexArray( 0 );

        //Swap front and back buffer after new thing has been drawn by application
        SDL_GL_SwapWindow(window);
    }

    //Prepare for cleanup
    glDeleteVertexArrays( 1, &vtxArrObjTri );
    glDeleteBuffers( 1, &vtxBufObjTri );

    //Delete OpenGL context, cleaning up the resources
    SDL_GL_DeleteContext(glContext);

    //Destroy working window
    SDL_DestroyWindow(window);
    
    //Destroy window (just in case) and graphics surface
    SDL_Quit();

    return EXIT_SUCCESS;
}
