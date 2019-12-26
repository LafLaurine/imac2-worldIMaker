#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/main.hpp>
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

int main(int argc, char** argv) {    
    constexpr int WINDOW_WIDTH = 900;
    constexpr int WINDOW_HEIGHT = 900;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "worldIMaker");
    SDL_WarpMouseInWindow(windowManager.m_window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // set users mouse positioin to the center  
    Overlay overlay;

    Scene scene;
    ProgramType FlatCube = ProgramType::FlatCube;
    ProgramType TexturedCube = ProgramType::TexturedCube;
    scene.loadProgram(FlatCube,"../shaders/colorCube.vs.glsl","../shaders/colorCube.fs.glsl");
    scene.loadProgram(TexturedCube,"../shaders/texturedCube.vs.glsl","../shaders/texturedCube.fs.glsl");
    scene.useProgram(FlatCube);
    scene.initAllCubes();
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
    scene.addLight();
/*
    if(TexturedCube == ProgramType::TexturedCube) {
        scene.useProgram(TexturedCube);
        scene.create_uniform_matrices(TexturedCube);
    }*/
   
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
        // Send event to ImGui
        ImGui_ImplSDL2_ProcessEvent(&e);
        switch (e.type) {
            case SDL_QUIT: windowManager.exit();

                case SDL_KEYDOWN:
                    gameController.handleScene(e,scene,cursor,overlay,camera);
                    gameController.handleCamera(e,camera);
                default : break;

			case SDL_MOUSEMOTION:
				/*if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_RIGHT)) {
					if (e.motion.xrel != 0) {
						camera.rotateRight(float(e.motion.xrel) * 1.0f);
					}
					if (e.motion.yrel != 0) {
						camera.rotateLeft(float(e.motion.yrel) * 1.0f);
					}
				}*/
			break;
        }
    }
        //Rendering code
        overlay.beginFrame(windowManager.m_window);
        overlay.drawOverlay(scene);
        scene.drawCubes(camera);
        scene.addLight();
        scene.recalculate_matrices(camera,cursor);
        cursor.draw();

        if(overlay.getClickedDayCube() &1) {
        }

        if(overlay.getClickedNightCube() &1) {
        }

        if(overlay.getClickedReset() &1) {
            gameController.cleanScene(scene.getAllCubes());
        }
        if(overlay.getClickedAddCube() &1) {
            gameController.addCube(scene,cursor);
        }
        if(overlay.getClickedDeleteCube() &1) {
            gameController.deleteCube(scene,cursor);
        }
        if(overlay.getClickedSave() &1) {
            std::string filename = "world.txt";
            std::cout << "Enter name of file : " << std::endl;
            std::cin >> filename;
            saveFile(filename,scene.getAllCubes());
        }
        if(overlay.getClickedLoad() &1) {
            std::string filename = "world.txt";
            std::cout << "Enter name of file : " << std::endl;
            std::cin >> filename;
            gameController.cleanScene(scene.getAllCubes());
            loadFile(filename,scene.getAllCubes());
        }
        if(overlay.getClickedRBF() &1) {
            applyRbf(scene.getAllCubes(), list_ctrl, FunctionType::InverseQuadratic);
        }

        if(overlay.getClickedSetGround() &1){
            scene.setGround();
        }
        overlay.endFrame(windowManager.m_window);
    }
    return EXIT_SUCCESS;
}