#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Scene.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

using namespace glimac;

//il faudra penser à ajouter -Werror au CMAKE, mais là c'est pas viable comme c'est la construction des fichiers

int main(int argc, char** argv) {    
    const int WINDOW_WIDTH = 900;
    const int WINDOW_HEIGTH = 900;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGTH, "worldIMaker");
    Overlay overlay;

    Scene scene;
    ProgramType FlatCube;
    CubeType CubeFlat;
    scene.loadProgram(FlatCube,"../shaders/3D.vs.glsl","../shaders/normal.fs.glsl");
    scene.useProgram(FlatCube);

    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);

    //Load camera
    FreeFlyCamera camera;
    //Load lights

    glClearColor(0.4, 0.6, 0.2, 1);

    // Application loop
    while(windowManager.isRunning()) {
        // Event loop
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            float zoom = 0.1f;
            float speed = 1.0f;
            switch (e.type) {
                case SDL_QUIT: windowManager.exit();
                /*case SDL_KEYDOWN:
                    if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        cube.setPositionX((cube.getPosition().x)-1);
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        cube.setPositionX((cube.getPosition().x)+1);
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                        cube.setPositionY((cube.getPosition().y)+1);
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        cube.setPositionY((cube.getPosition().y)-1);
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_PAGEUP) {
                        cube.setPositionZ((cube.getPosition().z)+1);
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_PAGEDOWN) {
                        cube.setPositionZ((cube.getPosition().z)-1);
                    } else if(e.key.keysym.sym == SDLK_z) {
                        camera.moveFront(zoom);
                    } else if (e.key.keysym.sym == SDLK_s) {
                        camera.moveFront(-zoom);
                    } else if (e.key.keysym.sym == SDLK_q) {
                        camera.moveLeft(zoom);              
                    } else if(e.key.keysym.sym == SDLK_d) {
                        camera.moveLeft(-zoom);              
                    }
                 break;*/
                case SDL_MOUSEWHEEL: 
                {
                    if (e.wheel.y > 0) {
                    camera.rotateUp(float(-e.wheel.y) * speed);
                    }
                    else if (e.wheel.y < 0) {
                    camera.rotateUp(float(e.wheel.y) * speed);
                    }
                }
                /*case SDL_BUTTON_MIDDLE:
                {
                    if (e.wheel.x < 0) {
                    camera.rotateLeft(float(e.wheel.x) * speed);
                    }
                    else if (e.wheel.x > 0) {
                    camera.rotateLeft(float(-e.wheel.x) * speed);
                    }
                }
                break;*/
                default : break;
            }

        }
            
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        overlay.beginFrame(windowManager.m_window);
        glm::mat4 globalMVMatrix =  camera.getViewMatrix();
        scene.loadScene(FlatCube,CubeFlat);
        scene.moveCube(CubeFlat);
        overlay.drawOverlay();
        scene.drawCube(CubeFlat);
        overlay.endFrame(windowManager.m_window);
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}