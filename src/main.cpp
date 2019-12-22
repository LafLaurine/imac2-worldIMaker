#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/GameController.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp>
#include <glimac/File.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Cursor.hpp>
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
    TrackballCamera camera;
    camera.setPosMatrix(5,5,5);
    GameController gameController;

    glClearColor(0.4, 0.6, 0.2, 1);
    scene.create_uniform_matrices(FlatCube);


    std::vector <ControlPoint> list_ctrl;
    readFileControl("controls.txt",list_ctrl);
    std::cout << list_ctrl.size() << std::endl;

    Cursor cursor;

    // Application loop
    while(windowManager.isRunning()) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: windowManager.exit();

                case SDL_KEYDOWN:
                    gameController.handleScene(e,scene,cursor);
                    gameController.handleCamera(e,camera);
                default : break;
        }
    }
        //Rendering code
        overlay.beginFrame(windowManager.m_window);
        overlay.drawOverlay();
        glm::vec3 color = glm::make_vec3(overlay.getColor());
        scene.drawCubes(camera,color);
        if(overlay.getClickedDayCube() &1) {
            scene.addLight();
        }

        if(overlay.getClickedNightCube() &1) {
            scene.removeLight();
        }
        scene.recalculate_matrices(camera,cursor,color);
        cursor.draw();
        if(overlay.getClickedAddCube() &1) {
            gameController.addCube(scene,cursor);
        }
        if(overlay.getClickedDeleteCube() &1) {
            gameController.deleteCube(scene,cursor);
        }
        if(overlay.getClickedSave() &1) {
            saveFile("world.txt",scene.getAllCubes());
        }
        if(overlay.getClickedChangeColor() &1){
            //gameController.changeColorCube(scene,cursor);
        }
        if(overlay.getClickedRBF() &1) {
            applyRbf(scene.getAllCubes(), list_ctrl, FunctionType::Gaussian);
        }
        overlay.endFrame(windowManager.m_window);
    }
    return EXIT_SUCCESS;
}