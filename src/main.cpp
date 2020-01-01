#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/main.hpp>
#include <glimac/GameController.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp>
#include <glimac/File.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Texture.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

using namespace glimac;

int main(int argc, char** argv) {    
    constexpr int WINDOW_WIDTH = 1200;
    constexpr int WINDOW_HEIGHT = 1200;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "worldIMaker");
    SDL_WarpMouseInWindow(windowManager.m_window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // set users mouse position to the center  

    //construct overlay
    Overlay overlay;
    //construct scene
    Scene scene;
    //get flatcube program, load it and use it
    ProgramType FlatCube = ProgramType::FlatCube;
    scene.loadProgram(FlatCube,"../shaders/colorCube.vs.glsl","../shaders/colorCube.fs.glsl");
    scene.useProgram(FlatCube);
    //initialize all of the scene cubes
    scene.initAllCubes();
    //initialize imgui
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
    //add light to the scene
    scene.addLight();
   
    //construct camera
    TrackballCamera camera;
    //construct freefly
    FreeFlyCamera freeCam;
    //set camera position
    camera.setPosMatrix(10,5,5);
    //construct gamecontroller
    GameController gameController;

    //set background color
    glClearColor(0.4, 0.6, 0.2, 1);
    //first initialization of uniform matrices
    scene.createUniformMatrices(FlatCube);


    //read control file for tree
    std::vector <ControlPoint> list_ctrlTree;
    readFileControl("controls.txt",list_ctrlTree);
    //read control file for big cube
    std::vector <ControlPoint> list_ctrlCube;
    readFileControl("otherControls.txt",list_ctrlCube);

    //construct cursor
    Cursor cursor;
    //set texture
    Texture texture("EarthMap.jpg",scene);


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
        //begin imgui
        overlay.beginFrame(windowManager.m_window);
        //draw tools
        overlay.drawOverlay(scene);
        //draw cubes
        scene.drawCubes(camera, texture.m_textureId);
        //add lights
        scene.addLight();
        scene.recalculateMatrices(camera,cursor);
        //draw cursor
        cursor.draw();

        //handle click on the overlay
        if(overlay.getClickedTree() &1) {
            applyRbf(scene.getAllCubes(), list_ctrlTree, FunctionType::InverseQuadratic);
        }
        if(overlay.getClickedCube() &1) {
            applyRbf(scene.getAllCubes(), list_ctrlCube, FunctionType::Gaussian);
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
        if(overlay.getClickedAddTexture() &1) {
            gameController.setTextureCube(scene,cursor, texture);
        }
        if(overlay.getClickedRemoveTexture() &1) {
            gameController.removeTextureCube(scene,cursor, texture);
        }
        //end imgui
        overlay.endFrame(windowManager.m_window);
    }
    return EXIT_SUCCESS;
}