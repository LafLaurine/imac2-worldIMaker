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
    const int WINDOW_HEIGHT = 900;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "worldIMaker");
    SDL_WarpMouseInWindow(windowManager.m_window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // set users mouse positioin to the center  
    Overlay overlay;

    Scene scene;
    ProgramType FlatCube;
    scene.loadProgram(FlatCube,"../shaders/3D.vs.glsl","../shaders/normal.fs.glsl");
    scene.useProgram(FlatCube);
    scene.initAllCubes();
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
   
    //Load camera
    FreeFlyCamera camera;
    GameController gameController;

    glClearColor(0.4, 0.6, 0.2, 1);
    glm::ivec2 mouse = glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    bool mouseDown = false;
    scene.create_uniform_matrices(FlatCube);

    // Application loop
    while(windowManager.isRunning()) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: windowManager.exit();
                case SDL_MOUSEBUTTONDOWN:
                    mouseDown = true;
                    mouse = windowManager.getMousePosition();
                    std::cout << windowManager.getMousePosition() << std::endl;
                    gameController.selectCube(scene, mouse);
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

                case SDL_KEYDOWN:
                    gameController.handleScene(e,scene);
                    gameController.handleCamera(e,camera);
                default : break;
        }
    }
        //Rendering code
        overlay.beginFrame(windowManager.m_window);
        overlay.drawOverlay();
        scene.drawCubes(camera);
        overlay.endFrame(windowManager.m_window);
    }
    return EXIT_SUCCESS;
}