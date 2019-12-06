#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/Program.hpp> 
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
    
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGTH = 720;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGTH, "worldIMaker");

    Overlay overlay;

    //Load shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/normal.fs.glsl");
    program.use();


    //Recupère variables uniformes
    GLint uModelLocation = glGetUniformLocation(program.getGLId(), "uModel");
    GLint uViewProjLocation = glGetUniformLocation(program.getGLId(), "uViewProj");

    Cube cube;

    const GLuint VERTEX_ATTR_POSITION = 0;

    glVertexAttribPointer(
    VERTEX_ATTR_POSITION, // index
    3, // size
    GL_FLOAT, // type
    GL_FALSE, // normalized
    3 * sizeof(float), // stride
    NULL // pointer
    );
    
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);

    //Load camera

    //Load lights

    //Calcul model matrix
    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 viewProjMat = projMat * viewMat;

    // Application loop
    while(windowManager.isRunning()) {
        // Event loop
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
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
                    }
                default : break;
            }

        }
            
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glUniformMatrix4fv(uModelLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(modelMat)); // Value
        
        glUniformMatrix4fv(uViewProjLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(viewProjMat)); // Value

        cube.display();
        overlay.beginFrame(windowManager.m_window);
        overlay.drawOverlay();
        overlay.endFrame(windowManager.m_window);
        //Update display
        glBindVertexArray(0);
        windowManager.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(&windowManager.m_glContext);
    SDL_DestroyWindow(windowManager.m_window);

    return EXIT_SUCCESS;
}