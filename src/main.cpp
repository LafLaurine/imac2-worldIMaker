#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/GameController.hpp>
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
    scene.loadProgram(FlatCube,"../shaders/3D.vs.glsl","../shaders/normal.fs.glsl");
    scene.useProgram(FlatCube);

    Cube cube;

    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
   
    //Load camera
    FreeFlyCamera camera;

    glClearColor(0.4, 0.6, 0.2, 1);
    glm::ivec2 mouse;
    bool mouseDown = false;
    scene.create_uniform_matrices(FlatCube);

    // Application loop
    while(windowManager.isRunning()) {
        SDL_Event e;
        float zoom = 0.1f;

        while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: windowManager.exit();
            case SDL_KEYDOWN:
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
                } if(e.key.keysym.sym == SDLK_z) {
                    camera.moveFront(zoom);
                } else if (e.key.keysym.sym == SDLK_s) {
                    camera.moveFront(-zoom);
                } else if (e.key.keysym.sym == SDLK_q) {
                    camera.moveLeft(zoom);              
                } else if(e.key.keysym.sym == SDLK_d) {
                    camera.moveLeft(-zoom);              
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseDown = true;
                    mouse = windowManager.getMousePosition();
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouseDown = false;
                    break;

                case SDL_MOUSEMOTION:
                    if(mouseDown) {
                        glm::ivec2 offsetMouse = windowManager.getMousePosition() - mouse;
                        mouse = windowManager.getMousePosition();
                        camera.rotateUp(offsetMouse.y/2.f);
                        camera.rotateLeft(offsetMouse.x/2.f);
                    }
                break;
                default : break;
        }
    }
        //Rendering code
        overlay.beginFrame(windowManager.m_window);
        scene.recalculate_matrices(camera,cube);
        overlay.drawOverlay();
        cube.draw();
        overlay.endFrame(windowManager.m_window);
    }
    return EXIT_SUCCESS;
}