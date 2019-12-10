#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/Program.hpp> 
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp>
#include <glimac/Cube.hpp> 
#include <glimac/glm.hpp> 
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

    //Load shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram("../shaders/3D.vs.glsl",
                                  + "../shaders/normal.fs.glsl");
    program.use();

    Cube cube;
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);


    GLuint uMVPLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLuint uMVLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");

    glm::mat4 modelMat = glm::mat4(1.0f);

    glUniformMatrix4fv(uMVLocation, // Location
                        1, // Count
                        GL_FALSE, // Transpose
                        glm::value_ptr(modelMat)); // Value

    glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGTH), 0.1f, 100.0f);
    glm::mat4 viewProjMat = projMat * viewMat;
    

    glUniformMatrix4fv(uMVPLocation, // Location
                        1, // Count
                        GL_FALSE, // Transpose
                        glm::value_ptr(viewProjMat)); // Value
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
                case SDL_KEYDOWN:
                    if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        cube.m_position.x--;
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        cube.m_position.x++;
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                        cube.m_position.y++;
                        std::cout << "cube.m_position : = " << cube.m_position << std::endl;
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        cube.m_position.y--;
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_PAGEUP) {
                        cube.m_position.z++;
                    } else if (e.key.keysym.scancode == SDL_SCANCODE_PAGEDOWN) {
                        cube.m_position.z--;
                    } else if(e.key.keysym.sym == SDLK_z) {
                        camera.moveFront(zoom);
                    } else if (e.key.keysym.sym == SDLK_s) {
                        camera.moveFront(-zoom);
                    } else if (e.key.keysym.sym == SDLK_q) {
                        camera.moveLeft(zoom);              
                    } else if(e.key.keysym.sym == SDLK_d) {
                        camera.moveLeft(-zoom);              
                    }
                 break;
                case SDL_MOUSEWHEEL: 
                {
                    if (e.wheel.y > 0) {
                    camera.rotateUp(float(e.wheel.y) * speed);
                    }
                    else if (e.wheel.y < 0) {
                    camera.rotateUp(float(-e.wheel.y) * speed);
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
        cube.initCube(); 
        glm::mat4 globalMVMatrix =  camera.getViewMatrix();
       
        //move cube
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cube.m_position);
        glUniformMatrix4fv(uMVLocation, // Location
                        1, // Count
                        GL_FALSE, // Transpose
                        glm::value_ptr(modelMat * globalMVMatrix));
        
        overlay.drawOverlay();
        cube.draw();
        overlay.endFrame(windowManager.m_window);
    }

    return EXIT_SUCCESS;
}