#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/Program.hpp> 
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/Overlay.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/glm.hpp> 
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

using namespace glimac;

//il faudra penser à ajouter -Werror au CMAKE, mais là c'est pas viable comme c'est la construction des fichiers

int main(int argc, char** argv) {
    
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGTH = 720;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGTH, "worldIMaker");

    //Load shaders

    //Load textures

    //Load camera

    //Load lights

    // Application loop
    while(windowManager.isRunning()) {
        // Event loop:
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                windowManager.exit(); // Leave the loop after this iteration
            }
        }
            
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //Update display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}