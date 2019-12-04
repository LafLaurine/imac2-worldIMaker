#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/Program.hpp> 
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp> 
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
   /* FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/normal.fs.glsl");
    program.use();*/


    //Recupère variables uniformes
  /*  GLint uMVPLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");*/


    //Load textures
    /*Cube cube;

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_COORDS = 2;

    glVertexAttribPointer(
    VERTEX_ATTR_POSITION, // index
    3, // size
    GL_FLOAT, // type
    GL_FALSE, // normalized
    3 * sizeof(float), // stride
    NULL // pointer
    );

    glVertexAttribPointer(
        VERTEX_ATTR_COORDS, // index
        2, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized
        3 * sizeof(float), // stride
        NULL // pointer
    );
  
    glVertexAttribPointer(
        VERTEX_ATTR_NORMAL, // index
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized
        3 * sizeof(float), // stride
        NULL // pointer
    );

    glm::mat4 ProjMatrix,MVMatrix, NormalMatrix;
    //Calcul de la matrice de projection
    ProjMatrix = glm::perspective(glm::radians(70.f),(float) (WINDOW_WIDTH / WINDOW_HEIGTH),0.1f,100.f);

    //Calcul de la matrice MV
    MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));  

    //Calcul de la NormalMatrix 
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
*/

    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);

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
   /*       glUniformMatrix4fv(uMVPLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(ProjMatrix * MVMatrix)); // Value
        
        glUniformMatrix4fv(uMVLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(MVMatrix)); // Value

        glUniformMatrix4fv(uNormalLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(NormalMatrix)); // Value

        cube.display();*/
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