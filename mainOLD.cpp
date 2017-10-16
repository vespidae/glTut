#include <iostream>
#include <SDL2/SDL.h>
#include "../../lib/display.cpp"
//#include "mesh.h"
//#include "shader.h"
//#include "texture.h"
//#include "transform.h"
//#include "camera.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Hello World!");

	//SDL_Event e;
	//bool isRunning = true;
	while(!display.IsClosed())
	{
            display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
            display.Update();
	}

	return 0;
}
